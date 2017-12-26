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


%macro EXCEPTION_COMMON_WITH_ERROR 1
global hal_exception_%1
hal_exception_%1:
    cli
    ; Stack already contains an error code.
    push byte %1
    jmp hal_exception_common
    iret
%endmacro


%macro EXCEPTION_COMMON_NO_ERROR 1
global hal_exception_%1
hal_exception_%1:
    cli
    push byte 0 ; Push a fake error code to the stack.
    push byte %1
    jmp hal_exception_common
    iret
%endmacro

section .text

; Generate ISR handlers -- exceptions 0 to 31.
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

; ISRs 0-7 don't include an error.
%assign i 0
%rep    8 ; 0-7 = 8 total.
  EXCEPTION_COMMON_NO_ERROR i
%assign i i + 1
%endrep


EXCEPTION_COMMON_WITH_ERROR 8
EXCEPTION_COMMON_NO_ERROR   9


; ISRs 10-14 include an error.
%assign i 10
%rep    5 ; 10-14 = 5 total.
  EXCEPTION_COMMON_WITH_ERROR i
%assign i i + 1
%endrep


; ISRs 15-31 don't include an error.
%assign i 15
%rep    16 ; 15-31 = 16 total.
  EXCEPTION_COMMON_NO_ERROR i
%assign i i + 1
%endrep

; Generate IRQ handlers.

; IRQs don't include an error.
; There are 16 IRQs (0-15), which map to exceptions 32 to 47.
%assign i 32
%rep    16 ; 32-47 = 16 total.
  EXCEPTION_COMMON_NO_ERROR i
%assign i i + 1
%endrep
