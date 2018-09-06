(* *** Types *** *)

type tool_flags = { asm  : string list;
                    cc   : string list;
                    ld   : string list;
                    qemu : string list }
type platform = { name  : string;
                  flags : tool_flags;
                  (* TODO: qemu is a tool. it should be identified as such. *)
                  qemu  : string }

(* Note: the `cmd` type is only here to ease debugging.
 * Getting errors about "string list list list" vs "string list list" is
 * less than great, and I found that this helped. *)
type cmd = { cmd : string list }

(* *** Execute programs *** *)

(* Execute a program, print its output, and return its exit code. *)
let exec env (cmd_name::args as cmd) =
  let check_exit_status =
    function
    | Unix.WEXITED 0 -> ()
    | Unix.WEXITED r -> exit r
    | Unix.WSIGNALED n -> exit 1
    | Unix.WSTOPPED n -> exit 1
  in
  let cmd'   = Array.of_list cmd    in
  let env'   = Array.of_list env    in
  let _, stdin' = Unix.pipe ~cloexec:true () in
  let pid =
    Unix.create_process_env cmd_name cmd' env' stdin' Unix.stdout Unix.stderr
  in
  let _, status = Unix.waitpid [] pid in
  check_exit_status status

(* *** Filename-manipulation functions. *** *)

let ends_with str suffix =
  suffix = Str.last_chars str (String.length suffix)
let ends_with_any suffixes str =
  List.exists (ends_with str) suffixes

let exe_for file = Filename.remove_extension file ^ ".exe"
let lib_for file = Filename.remove_extension file ^ ".a"
let obj_for file = Filename.remove_extension file ^ ".o"

(* *** Functions for finding source files. *** *)

let find dir =
  let rec walk acc paths =
    match paths with
    | []        -> acc
    | dir::tail ->
        let contents = Array.to_list (Sys.readdir dir) in
        let contents = List.rev_map (Filename.concat dir) contents in
        let dirs, _  = List.partition Sys.is_directory contents in
        walk (contents @ acc) (dirs @ tail)
  in
  walk [] [dir]

let find_by_ext dir suffixes =
  List.filter (ends_with_any suffixes) @@ find dir

let find_src_files dir subdir exts =
  find_by_ext (Filename.concat dir subdir) exts

let find_platform_files dir platform_name exts =
  let path = Filename.concat dir platform_name in
  if Sys.file_exists path && Sys.is_directory path then
      find_by_ext path exts
  else
      []

let target_files exts category name platform_name =
  let catdir = Filename.concat "src"  category in
  let dir    = Filename.concat catdir name in
  find_src_files        dir "src"         exts @
  find_platform_files   dir platform_name exts


(* *** String manipulation functions. *** *)

let rec sort_strings lst =
  match lst with
  | []         -> []
  | [a]        -> [a]
  | a::b::tail ->
    if a <= b
    then [a; b] @ (sort_strings tail)
    else [b; a] @ (sort_strings tail)

(* *** Handle command-line arguments. *** *)

let parse_cli_args argv =
  let args          = List.tl (Array.to_list Sys.argv) in
  let flags, args   = List.partition (fun s -> String.get s 0 == '-') args in
  let vars, targets = List.partition (fun s -> String.contains s '=') args in
  (vars, targets)

