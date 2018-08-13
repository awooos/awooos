#!/usr/bin/runghc

module Main where

import Data.Char
import Data.List

data Build = Build { build_platform :: String
                   , build_type     :: String }

data Tools = Tools { ar :: String
                   , as :: String
                   , cc :: String
                   , ld :: String }

data Flags = Flags { ar_flags :: List
                   , as_flags :: List
                   , cc_flags :: List
                   , ld_flags :: List
                   , qemu_flags :: List }

data Project = Project { name :: String
                       , scm  :: String
                       , version    :: String
                       , categories :: List
                       , build_root :: String
                       , build_types :: List }

data Platform = Platform { platform_name  :: String
                         , platform_flags :: Flags
                         , platform_qemu  :: String }

project = Project { name    = "awooos"
                  , scm     = "todo"
                  , version = "{{scm.tag_or_revision}}-{{build.type}}"
                  , categories = ["executables", "libraries"]
                  , build_root = "./src"
                  , build_types = ["test", "debug", "release"] }

tools = Tools { ar="ar"
              , as="nasm"
              , cc="clang"
              , ld="ld" }

build = Build { build_platform  = "i386"
              , build_type      = "debug" }

flags = Flags { cc_flags    = ["-std=c11", "-pedantic-errors", "-gdwarf-2",
                               "-nostdinc", "-ffreestanding",
                               "-fno-stack-protector", "-fno-builtin",
                               "-fdiagnostics-show-option",
                               "-Werror", "-Weverything", "-Wno-cast-qual",
                               "-Wno-missing-prototypes", "-Wno-vla"]
              , ld_flags    = []
              , as_flags    = []
              , qemu_flags  = [] }

i386_flags = Flags { cc_flags   = ["-m32"]
                   , ld_flags   = ["-melf_i386"]
                   , as_flags   = ["-felf32"]
                   , qemu_flags = ["-no-reboot", "-device",
                                  "isa-debug-exit,iobase=0xf4,iosize=0x04"] }
--tools.qemu = qemu-system-i386

-- TODO: "qemu" is a tool. it should be identified as such.
i386 = Platform { platform_name="i386"
                , platform_flags=i386_flags
                , platform_qemu="qemu-system-i386" }


command (xs:".c") = ""
--command xs:".":"c" = ""

{-
[artifacts:.c]
# artifacts.c_includes is an array which contains
# "-I /path/to/:category/:artifact_name/include" for each artifact.
command =
    ${tools:cc} -c ${flags.cc} ${platform:flags.cc}
      {artifacts.c_includes} -o {name}.o {name}.c
suffix = .o

[artifacts:.asm]
command = {tools.as} {platform:flags.as} -o {name}.o {name}.asm
suffix = .o

[categories:libraries]
requires =
    artifacts.{category}.c
    artifacts.{category}.asm
command = {tools.ar} rcs {output_file} {build.artifacts}
suffix = .a

[categories:executables]
require =
    libraries
command =
    ${tools:ld} -o {artifact.file} -Lsrc/libraries
      ${flags.ld} -T src/link-${build.platform}.ld
      {artifacts.asm} {artifacts.c} {category.libraries.artifacts}
suffix = .exe

# TODO: This feels a bit clumsy, to put it mildly.
[file:isofs]
copy =
    assets/isofs/               isofs/
    {categories.executables}  isofs/system/

[file:iso]
require =
    executables:kernel
    file:isofs
command =
    xorriso -as mkisofs -boot-info-table -R -b boot/grub/stage2_eltorito
      -no-emul-boot -boot-load-size 4 -input-charset utf-8
      -o ${project:name}-${build.platform}-${build.type}.iso isofs/
suffix = .iso

[task:qemu]
require =
    file:iso
# Not sure about the {artifacts.file.iso} thing.
command =
  ${platform:tools.qemu} ${flags.qemu} ${platform:flags.qemu} -vga std
    -serial stdio -cdrom {artifacts.file.iso}

-}

rule :: String -> String
rule x = x

library    name args = rule ("libraries."   ++ name) args
executable name args = rule ("executables." ++ name) args

-- Aliases
all    = kernel
kernel = executable "kernel"
iso    = files "iso"

main = do
  print "awoo"

