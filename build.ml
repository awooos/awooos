#!/usr/bin/env ocaml
#load "str.cma"
#load "unix.cma"

let libraries = [
  "hal";
  "cadel";
  "flail";
  "greeter";
  "tinker";
  "ali";
  "tests";
  "shell";
  "dmm";
]

let env, targets, flags =
  let args          = List.tl (Array.to_list Sys.argv) in
  let flags, args   = List.partition (fun s -> String.get s 0 == '-') args in
  let vars, targets = List.partition (fun s -> String.contains s '=') args in
  (vars, targets, flags)

let exec (cmd_name::args as cmd) =
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

(* Filename-manipulation functions. *)

let ends_with str suffix =
  suffix = Str.last_chars str (String.length suffix)
let ends_with_any suffixes str =
  List.exists (ends_with str) suffixes

let exe_for file = Filename.remove_extension file ^ ".exe"
let lib_for file = Filename.remove_extension file ^ ".a"
let obj_for file = Filename.remove_extension file ^ ".o"

(* Types *)

type tool_flags = { asm  : string list;
                    ar   : string list;
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

(* Functions for finding source files. *)

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

let find_by_ext dir suffixes = List.filter (ends_with_any suffixes) @@ find dir

let find_src_files dir subdir exts =
  find_by_ext (Filename.concat dir subdir) exts
let find_platform_files dir platform_name exts =
  let path = Filename.concat dir platform_name in
  if Sys.file_exists path && Sys.is_directory path then
      find_by_ext path exts
  else
      []
let target_files category name platform_name =
  let exts   = [".c"; ".asm"] in
  let catdir = Filename.concat "src"  category in
  let dir    = Filename.concat catdir name in
  find_src_files        dir "src"         exts @
  find_platform_files   dir platform_name exts


(* General tool flags *)

let lib_include_flag lib = "-Isrc/libraries/" ^ lib ^ "/include"
let flags = { asm   = [];
              ar    = [];
              cc    = ["-std=c11"; "-c"; "-pedantic-errors"; "-gdwarf-2";
                       "-nostdinc"; "-ffreestanding";
                       "-fno-stack-protector"; "-fno-builtin";
                       "-fdiagnostics-show-option";
                       "-Werror"; "-Weverything"; "-Wno-cast-qual";
                       "-Wno-missing-prototypes"; "-Wno-vla";
                       "-Iinclude/"] @
                      List.map lib_include_flag libraries;
              ld    = ["-nostdlib"; "-g"; "--whole-archive";
                       "-L"; "src/libraries"];
              qemu  = [] }

(* Platform flags *)

let i386_flags = { ar   = [];
                   asm  = ["-felf32"];
                   cc   = ["-m32"];
                   ld   = ["-melf_i386"];
                   qemu = ["-no-reboot"; "-device";
                           "isa-debug-exit;iobase=0xf4;iosize=0x04"] }

(* Platforms *)

let i386 = { name  = "i386";
             flags = i386_flags;
             qemu  = "qemu-system-i386" }

(* Build commands and configuration. *)

let platform = i386
let ar  file args =
  {cmd=["ar"; "rcs"] @ flags.ar  @ platform.flags.ar  @ [file] @ args}
let asm file args =
  {cmd=["nasm"]  @ flags.asm @ platform.flags.asm @ ["-o"; file] @ args}
let cc  file args =
  {cmd=["clang"] @ flags.cc  @ platform.flags.cc  @ ["-o"; file] @ args}
let ld  file args =
  {cmd=["ld"; "-o"; file] @ flags.ld @platform.flags.ld @ args}

(* Functions for creating build steps. *)

let build' file =
  let ext = Filename.extension file in
  match ext with
  | ".asm"  -> asm (obj_for file) [file]
  | ".c"    -> cc  (obj_for file) [file]
  | _       -> {cmd=[]}

let build files = List.map build' files

let library name =
  let artifacts = target_files "libraries" name platform.name in
  let artifacts' = List.map obj_for artifacts in
  [ build artifacts;
    [ar ("src/libraries/" ^ name ^ ".a") artifacts']]

let rec sort_strings lst =
  match lst with
  | []         -> []
  | [a]        -> [a]
  | a::b::tail ->
    if a <= b
    then [a; b] @ (sort_strings tail)
    else [b; a] @ (sort_strings tail)

let executable name ldflags libraries =
  let ld_library_flags =
    List.flatten @@ List.map (fun lib -> ["-l"; ":" ^ lib ^ ".a"]) libraries
  in
  let artifacts = target_files "executables" name platform.name in
  let artifacts' = List.map obj_for artifacts in
  (* HACK: Can we make this compile kernel.exe without sorting? *)
  let artifacts'' = sort_strings artifacts' in
  (* let filename = "src/executables/" ^ name ^ ".exe" in *)
  let filename = "src/" ^ name ^ ".exe" in
  [ build artifacts;
    [ld filename (ldflags @ artifacts'' @ ld_library_flags)]]

(* Functions for manipulating, printing, and executing rules/steps. *)

let steps_for   rule = List.map (fun x -> x.cmd) (List.flatten rule)
let print_step  step = print_endline @@ "$ " ^ String.concat " " step
let run_step    step =
  print_step step;
  exec       step
let fake_run    rule = List.map print_step  @@ steps_for rule
let real_run    rule = List.map run_step    @@ steps_for rule

let run ?(dry_run=false) rule =
  match dry_run with
  | true    -> fake_run rule
  | false   -> real_run rule

(* Aliases *)

let kernel =
  let ldflags = ["-T"; "src/link-" ^ platform.name ^ ".ld" ] in
  library "ali"     @
  library "cadel"   @
  library "dmm"     @
  library "flail"   @
  library "greeter" @
  library "hal"     @
  library "shell"   @
  library "tests"   @
  library "tinker"  @
  executable "kernel" ldflags libraries

let all    = kernel

let () =
  exec ["bash"; "-c"; "./bin/generate_build_info.sh test i386 > include/awoo/build_info.h"];
  ignore @@ run all
