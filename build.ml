#!/usr/bin/env ocaml
#load "str.cma"
#load "unix.cma"
#use "buildlib.ml"

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

(* Types *)

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

let target_files category name platform_name =
  let exts   = [".c"; ".asm"] in
  let catdir = Filename.concat "src"  category in
  let dir    = Filename.concat catdir name in
  find_src_files        dir "src"         exts @
  find_platform_files   dir platform_name exts


(* General tool flags *)

let lib_include_flag lib = "-Isrc/libraries/" ^ lib ^ "/include"
let flags = { asm   = [];
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

let i386_flags = { asm  = ["-felf32"];
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
let ar  file args = {cmd=["ar"; "rcs"; file] @ args}
let asm file args = {cmd=["nasm"; "-o"; file] @ platform.flags.asm @ args}
let cc  file args =
  {cmd=["clang"] @ flags.cc  @ platform.flags.cc  @ ["-o"; file] @ args}
let ld  file args =
  {cmd=["ld"; "-o"; file] @ flags.ld @ platform.flags.ld @ args}

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

let executable name ldflags libraries =
  let ld_library_flags =
    List.flatten @@ List.map (fun lib -> ["-l"; ":" ^ lib ^ ".a"]) libraries
  in
  let artifacts = target_files "executables" name platform.name in
  let artifacts' = List.map obj_for artifacts in
  (* HACK: Can we make this compile kernel.exe without sorting? *)
  let artifacts'' = sort_strings artifacts' in
  let filename = "src/executables/" ^ name ^ ".exe" in
  [ build artifacts;
    [ld filename (ldflags @ artifacts'' @ ld_library_flags)]]

(* Functions for manipulating, printing, and executing rules/steps. *)

let steps_for   rule = List.map (fun x -> x.cmd) (List.flatten rule)
let print_step  step = print_endline @@ "$ " ^ String.concat " " step
let run_step    step =
  print_step step;
  exec env step
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
  exec env ["bash"; "-c"; "./bin/generate_build_info.sh test i386 > include/awoo/build_info.h"];
  ignore @@ run all
