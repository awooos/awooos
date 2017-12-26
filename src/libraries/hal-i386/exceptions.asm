; ISR and IRQ handlers.

bits 32

extern hal_exception_handler

hal_exception_common:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, hal_exception_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret


%macro EXCEPTION_COMMON 1
global hal_exception_%1
hal_exception_%1:
    cli

    ; Exceptions 8 and 10-14 already push an error code to the stack.
    ; For everything else, we push a fake error code of zero.
    %ifn %1 == 8 || (%1 >= 10 && %1 <= 14)
      push 0 ; Fake error code.
    %endif

    push byte %1
    jmp hal_exception_common
    iret
%endmacro

section .text

; Generate ISR and IRQ handlers.
; - ISRs are exceptions 0 to 31.
; - IRQs are exceptions 32 to 47.
;
; Lots of inspiration, and documentation, from http://www.osdever.net/bkerndev/Docs/isrs.htm
;
; Exception # | Description                             | Has error code?
; =======================================================================
; 0           | Division By Zero Exception              | No
; 1           | Debug Exception                         | No
; 2           | Non Maskable Interrupt Exception        | No
; 3           | Breakpoint Exception                    | No
; 4           | Into Detected Overflow Exception        | No
; 5           | Out of Bounds Exception                 | No
; 6           | Invalid Opcode Exception                | No
; 7           | No Coprocessor Exception                | No
; 8           | Double Fault Exception                  | Yes
; 9           | Coprocessor Segment Overrun Exception   | No
; 10          | Bad TSS Exception                       | Yes
; 11          | Segment | Not Present Exception         | Yes
; 12          | Stack Fault Exception                   | Yes
; 13          | General Protection Fault Exception      | Yes
; 14          | Page Fault Exception                    | Yes
; 15          | Unknown Interrupt Exception             | No
; 16          | Coprocessor Fault Exception             | No
; 17          | Alignment Check Exception (486+)        | No
; 18          | Machine Check Exception (Pentium/586+)  | No
; 19 to 31    | Reserved Exceptions                     | No

%assign i 0
%rep 48
  EXCEPTION_COMMON i
%assign i i + 1
%endrep
