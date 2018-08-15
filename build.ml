#!/usr/bin/env ocaml

let ($) f x = f x

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
;;

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
  ["ar"]    @ flags.ar  @ platform.flags.ar  @ [file] @ args
let asm file args =
  ["nasm"]  @ flags.asm @ platform.flags.asm @ ["-o"; file] @ args
let cc  file args =
  ["clang"] @ flags.cc  @ platform.flags.cc  @ ["-o"; file] @ args
let ld  file args =
  ["ld"]    @ flags.ld  @ platform.flags.ld  @ ["-o"; file] @ args

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
  | _       -> []

let rec build = function
  | []          -> []
  | file::files -> (build' file (Filename.extension file)) @ (build files)

(* TODO: Actually get this list. *)
let library_files = function
  | "ali" -> ["foo.c"; "bar.asm"]
  | x     -> []
let library name =
  let artifacts = library_files name in
  [ build artifacts;
    ar name artifacts]

let executable_files = function
  | "kernel" -> [ "src/executables/kernel/main.c";
                  "src/executables/kernel/start-" ^ platform.name ^ ".asm"]
  | x        -> []
let executable name =
  let artifacts = executable_files name in
  [ build artifacts;
    cc name artifacts]

(*
executable name = do
  ali     <- library "ali"
  dmm     <- library "dmm"
  greeter <- library "greeter"
  run ["echo awoo"]
*)
(* Aliases *)
(*
all    = kernel
kernel = executable "kernel"
*)

let () =
  (*let steps = library "ali" in
  let lines = List.map (String.concat " ") steps in
  print_endline $ String.concat "\n" lines*)
  print_endline $ String.concat "\n" (find "src")
