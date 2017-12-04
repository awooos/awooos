global _start       ; Make entrypoint visible to linker.
global stack_bottom ; Bottom of the stack.
global stack_top    ; Top of the stack.
extern kernel_init  ; Defined in kernel/init.c.

; Amount of space to reserve for the stack.
STACKSIZE equ 0x4000 ; That's 16KB.

; Multiboot header. See GRUB documentation for details.
; TODO: Find link to GRUB documentation. ¯\_(ツ)_/¯
MODULEALIGN equ  1<<0            ; Align modules on page boundaries.
MEMINFO     equ  1<<1            ; Provide memory map.
FLAGS       equ  MODULEALIGN | MEMINFO  ; Multiboot flag field.
MAGIC       equ  0x1BADB002      ; Magic number so bootloader can find the header.
CHECKSUM    equ -(MAGIC + FLAGS) ; Checksum required.

; Executable section.
section .text
  align 4
  MultiBootHeader:
      dd MAGIC
      dd FLAGS
      dd CHECKSUM

  _start:
    mov  esp, stack_top   ; Set up the stack.
    push ebx              ; Argument to kernel_init.
    push eax              ; Provided by Multiboot-compliant bootloaders.

    call kernel_init      ; Call kernel proper.

    ; We only get here if the kernel returns.
    ; This, generally speaking, probably shouldn't happen.

    cli                   ; Stop interrupts.
    hlt                   ; Halt the machine.


; Data section.
section .bss
  stack_bottom:

  align 32
  resb STACKSIZE    ; Reserve stack on a quadword boundary.

  stack_top:

