#!/usr/bin/env ocaml
#load "str.cma"
#load "unix.cma"

let ($) f x = f x

let env, targets, flags =
  let args          = List.tl (Array.to_list Sys.argv) in
  let flags, args   = List.partition (fun s -> String.get s 0 == '-') args in
  let vars, targets = List.partition (fun s -> String.contains s '=') args in
  (vars, targets, flags)

let exec (cmd::args) =
  Unix.execvpe cmd (Array.of_list args) (Array.of_list env)

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

let find_by_ext dir suffixes = List.filter (ends_with_any suffixes) $ find dir

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

let flags = { asm   = [];
              ar    = [];
              cc    = ["-std=c11"; "-pedantic-errors"; "-gdwarf-2";
                       "-nostdinc"; "-ffreestanding";
                       "-fno-stack-protector"; "-fno-builtin";
                       "-fdiagnostics-show-option";
                       "-Werror"; "-Weverything"; "-Wno-cast-qual";
                       "-Wno-missing-prototypes"; "-Wno-vla"];
              ld    = ["-nostdlib"; "-g"; "-wholearchive"];
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

(* Functions for creating build steps. *)

let build' file ext = match ext with
  | ".asm"  -> asm (obj_for file) []
  | ".c"    -> cc  (obj_for file) []
  | _       -> {cmd=[]}

let rec build = function
  | []          -> []
  | file::files -> (build' file (Filename.extension file)) :: (build files)

let library name =
  let artifacts = target_files "libraries" name platform.name in
  [ build artifacts;
    [ar name artifacts]]

let executable name ldflags =
  let artifacts = target_files "executables" name platform.name in
  [ build artifacts;
    [ld name (artifacts @ ldflags)]]

(* Functions for manipulating, printing, and executing rules/steps. *)

let steps_for   rule = List.map (fun x -> x.cmd) (List.flatten rule)
let print_step  step = print_endline $ "$ " ^ String.concat " " step
let exec_step   step = ()
let run_step    step =
  print_step step;
  exec_step  step
let fake_run    rule = List.map print_step  $ steps_for rule
let real_run    rule = List.map run_step    $ steps_for rule

let run ?(dry_run=false) rule =
  match dry_run with
  | true    -> fake_run rule
  | false   -> real_run rule

(* Aliases *)

let kernel =
  let ldflags =
    [ "-L"; "src/libraries";
      "-T"; "src/link-" ^ platform.name ^ ".ld" ] @
    [ "-l"; ":ali.a"      ;
      "-l"; ":cadel.a"    ;
      "-l"; ":dmm.a"      ;
      "-l"; ":flail.a"    ;
      "-l"; ":greeter.a"  ;
      "-l"; ":hal.a"      ;
      "-l"; ":shell.a"    ;
      "-l"; ":tests.a"    ;
      "-l"; ":tinker.a"   ]
  in
  library "ali"     @
  library "cadel"   @
  library "dmm"     @
  library "flail"   @
  library "greeter" @
  library "hal"     @
  library "shell"   @
  library "tests"   @
  library "tinker"  @
  executable "kernel" ldflags

let all    = kernel

let () = ignore $ run all
