#!/bin/bash
ocamlc -o "$0.bin" -pp 'sed "1,3 s/^.*//"' "$0" && "$0.bin"; STATUS=$?
[ -f "$0.bin" ] && rm "$0.bin"; exit $STATUS
(* BEGIN ACTUAL OCAML CODE. *)

let ($) f x = f x
let rec last = function
  | [x]   -> x
  | xs::x -> last x

let extname file = last (String.split_on_char '.' file)
let with_suffix file ext = (List.hd (String.split_on_char '.' file)) ^ ext
let exe_for file = with_suffix file ".exe"
let lib_for file = with_suffix file ".a"
let obj_for file = with_suffix file ".o"

(* let run cmd args = exec cmd args *)
(* let run cmd args = [] *)

type tool_flags = { asm  : string list;
                    ar   : string list;
                    cc   : string list;
                    ld   : string list;
                    qemu : string list }
type platform = { name  : string;
                  flags : tool_flags;
                  (* TODO: "qemu" is a tool. it should be identified as such. *)
                  qemu  : string }

(* ------------- *)

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

let i386_flags = { ar   = [];
                   asm  = ["-felf32"];
                   cc   = ["-melf_i386"];
                   ld   = [];
                   qemu = ["-no-reboot"; "-device";
                           "isa-debug-exit;iobase=0xf4;iosize=0x04"] }

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
  | "asm" -> asm $ obj_for file
  | "c"   -> cc  $ obj_for file
  | _     -> function _ -> []

let rec build = function
  | []          -> []
  | file::files -> (build' file (extname file)) :: (build files)

(* TODO: Actually get this list. *)
let library_files = function
  | "ali" -> ["foo.c"; "bar.asm"]
  | x     -> []
let library name =
  let artifacts = library_files name in
(*  let commands = build artifacts in*)
  let commands = [["foo"; "bar"]] in
  let ar_cmd = [["ar"; name] @ artifacts] in
  commands @ ar_cmd

let executable_files = function
  | "kernel" -> [ "src/executables/kernel/main.c";
                  "src/executables/kernel/start-" ^ platform.name ^ ".asm"]
  | x        -> []
let executable name =
  let artifacts = executable_files name in
  (*build artifacts @ [["cc"; "-o"; name] @ artifacts]*)
  [["clang"]]

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
  let steps = library "ali" in
  let lines = List.map (String.concat " ") steps in
  print_endline $ String.concat "\n" lines
