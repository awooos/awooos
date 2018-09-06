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

(* *** String manipulation functions. *** *)

let rec sort_strings lst =
  match lst with
  | []         -> []
  | [a]        -> [a]
  | a::b::tail ->
    if a <= b
    then [a; b] @ (sort_strings tail)
    else [b; a] @ (sort_strings tail)

