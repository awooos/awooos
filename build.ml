#!/usr/bin/env ocaml
#load "str.cma"

let ($) f x = f x

let ends_with str suffix =
  suffix = Str.last_chars str (String.length suffix)
let ends_with_any suffixes str =
  List.exists (ends_with str) suffixes

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

let find_by_ext dir suffixes = List.filter (ends_with_any suffixes) $ find dir

let exe_for file = Filename.remove_extension file ^ ".exe"
let lib_for file = Filename.remove_extension file ^ ".a"
let obj_for file = Filename.remove_extension file ^ ".o"

(* let run cmd args = exec cmd args *)
(* let run cmd args = [] *)

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

(* General tool flags *)

let flags = { asm   = [];
              ar    = [];
              cc    = ["-std=c11"; "-pedantic-errors"; "-gdwarf-2";
                       "-nostdinc"; "-ffreestanding";
                       "-fno-stack-protector"; "-fno-builtin";
                       "-fdiagnostics-show-option";
                       "-Werror"; "-Weverything"; "-Wno-cast-qual";
                       "-Wno-missing-prototypes"; "-Wno-vla"];
              ld    = [];
              qemu  = [] }

(* Platform flags *)

let i386_flags = { ar   = [];
                   asm  = ["-felf32"];
                   cc   = ["-melf_i386"];
                   ld   = [];
                   qemu = ["-no-reboot"; "-device";
                           "isa-debug-exit;iobase=0xf4;iosize=0x04"] }

(* Platforms *)

let i386 = { name  = "i386";
             flags = i386_flags;
             qemu  = "qemu-system-i386" }

(* Build commands and configuration. *)

let platform = i386
let ar  file args =
  {cmd=["ar"]    @ flags.ar  @ platform.flags.ar  @ [file] @ args}
let asm file args =
  {cmd=["nasm"]  @ flags.asm @ platform.flags.asm @ ["-o"; file] @ args}
let cc  file args =
  {cmd=["clang"] @ flags.cc  @ platform.flags.cc  @ ["-o"; file] @ args}
let ld  file args =
  {cmd=["ld"]    @ flags.ld  @ platform.flags.ld  @ ["-o"; file] @ args}

(* TARGETS *)

(* TODO: Get this list automatically. *)
let libs =
  ["ali";
   "cadel";
   "dmm";
   "flail";
   "greeter";
   "hal";
   "shell";
   "tests";
   "tinker"]

let ali_files = [
  "src/libraries/ali/src/assert.c";
  "src/libraries/ali/src/event.c";
  "src/libraries/ali/src/main.c";
  "src/libraries/ali/src/main_test.c";
  "src/libraries/ali/src/number/main.c";
  "src/libraries/ali/src/number/main_test.c";
  "src/libraries/ali/src/str/charsplit.c";
  "src/libraries/ali/src/str/charsplit_test.c";
  "src/libraries/ali/src/string.c";
  "src/libraries/ali/src/str/shellsplit.c";
  "src/libraries/ali/src/str/shellsplit_test.c";
  "src/libraries/ali/src/str/test.c";
  "src/libraries/ali/src/text.c"
]

let build' file ext = match ext with
  | ".asm"  -> asm (obj_for file) []
  | ".c"    -> cc  (obj_for file) []
  | _       -> {cmd=[]}

let rec build = function
  | []          -> []
  | file::files -> (build' file (Filename.extension file)) :: (build files)

(* TODO: Actually get this list. *)
let library_files = function
  | "ali" -> ["foo.c"; "bar.asm"]
  | x     -> []
let library name =
  let artifacts = library_files name in
  [ build artifacts;
    [ar name artifacts]]

let executable_files = function
  | "kernel" -> [ "src/executables/kernel/main.c";
                  "src/executables/kernel/start-" ^ platform.name ^ ".asm"]
  | x        -> []
let executable name =
  let artifacts = executable_files name in
  [ build artifacts;
    [cc name artifacts]]

(*
executable name = do
  ali     <- library "ali"
  dmm     <- library "dmm"
  greeter <- library "greeter"
  run ["echo awoo"]
*)
(* Aliases *)

let kernel =
  executable "kernel"

let all    = kernel

let print_step  step  = print_endline $ String.concat " " step.cmd
let print_steps steps = List.map print_step  steps
let print_obj   objs  = List.map print_steps objs

let step  step  = String.concat " " step.cmd
let steps steps = List.map (step)  steps
let rule  rule  = List.map (steps) rule

let () =
  let stps = List.flatten $ List.map steps all in
  print_endline $ (String.concat "\n" stps)
