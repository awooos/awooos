#!/bin/bash
ocamlc -o "$0.bin" -pp 'sed "1,3 s/^.*//"' "$0" && "$0.bin"; STATUS=$?
[ -f "$0.bin" ] && rm "$0.bin"; exit $STATUS
(* BEGIN ACTUAL OCAML CODE. *)

let object_for file = (List.hd (String.split_on_char '.' file)) ^ ".o"
(* let run file cmd args = exec cmd (args @ [file]) *)
let run file cmd args = []

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

let platform = i386

let ar  file = run file "ar"    (flags.cc @ platform.flags.cc)
let asm file = run file "nasm"  []
let cc  file = run file "clang" []
let ld  file = run file "ld"    []

let () =
  print_endline (object_for "foo.c");
  print_endline (object_for "foo.asm");
