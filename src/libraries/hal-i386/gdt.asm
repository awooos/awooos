; asmsyntax=nasm

; Borrowed with love from a prior operating system development excursion.
; https://github.com/duckinator/dux/blob/main/src/lib/hal/gdt.asm

bits 32

global hal_gdt_init
global hal_gdt_load_esp0_into_tss
global hal_tss_flush
extern stack_top

section .text
    hal_gdt_init:
        ; Load the GDT and reload cs to 0x8 with a far jump (to the next line)
        ; the code there reloads ds, es, fs, gs, and ss with 0x10
        ; See the comments in the GDT for what 0x8 and 0x10 do
        lgdt [_gdt_desc]
        jmp 0x8:.reload
    .reload:
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        ; Load the TSS. Some docs are in the Intel manuals and
        ; http://wiki.osdev.org/Task_State_Segment

        ; First I'm going to fill in the fields of the GDT descriptor for
        ; the TSS. This is mostly a bunch of bitshifts to align everything
        ; correctly

        ; eax will be the beginning of the TSS
        ; ebx will be the size of the TSS
        mov eax, _tss_begin
        mov ebx, _tss_end
        sub ebx, _tss_begin

        ; The first 16 bits of the limit (size of TSS).
        mov ecx, ebx
        and ecx, 0xff
        mov esi, _gdt_tss
        mov word [ds:esi], cx

        ; The last 4 bits of the limit.
        mov ecx, ebx
        shl ecx, 16
        and ecx, 0xf

        mov esi, _gdt_tss
        add esi, 6
        mov byte dl, [ds:esi]
        or dl, cl
        mov byte [ds:esi], dl

        ; The first 16 bits of the base (location of TSS).
        mov ecx, eax
        and ecx, 0xffff
        mov esi, _gdt_tss
        add esi, 2
        mov word [ds:esi], cx

        ; The middle 8 bits of the base.
        mov ecx, eax
        shl ecx, 16
        and ecx, 0xff
        mov esi, _gdt_tss
        add esi, 4
        mov byte [ds:esi], cl

        ; The last 8 bits of the base (finally).
        mov ecx, eax
        shl ecx, 24
        and ecx, 0xff
        mov esi, _gdt_tss
        add esi, 7
        mov byte [ds:esi], cl

        ; Ok, now that the GDT is in place, I need to fill in the stack
        ; data to the actual TSS.

        ; Load ESP0. For the time being, this will be the top of the stack.
        ; Before attempting to use this TSS for task switching, please please
        ; please load ESP0 with the current value of ESP0 or expect
        ; crashes (that I will laugh at since you don't read my docs).
        ; This is almost identical to gdt_load_esp0_into_tss. I am just
        ; inlining it for speed.
        mov esi, stack_top
        mov esi, 4
        mov dword [ds:esi], eax

        ; Load SS0
        mov ax, 0x10
        mov esi, 8
        mov word [ds:esi], ax

        ; This falls through to hal_tss_flush.

    ; Finally, we can load the valid TSS into the task register. The
    ; TSS is at offset 28 in the GDT.
    hal_tss_flush:
        mov ax, 0x28
        ltr ax
        ; Finished
        ret

    ; A function to load a value into ESP0 in the TSS.
    hal_gdt_load_esp0_into_tss:
        ; First argument will contain the value to load in esp0
        mov eax, [esp + 4]
        mov eax, stack_top
        mov esi, 4
        mov dword [ds:esi], eax
        ret

section .data
    _gdt_begin:
        ; For reference, the format of the GDT can be found in both the
        ; Intel 64/IA-32 manuals and on http://wiki.osdev.org/GDT

    _gdt_null: ; 0x0
        dq 0

    _gdt_code: ; 0x8
        dw 0xffff
        dw 0x0
        db 0x0
        db 10011010b
        db 11001111b
        db 0x0

    _gdt_data: ; 0x10
        dw 0xffff
        dw 0x0
        db 0x0
        db 10010010b
        db 11001111b
        db 0x0

    _gdt_user_code: ; 0x18
        dw 0xffff
        dw 0x0
        db 0x0
        db 11111010b
        db 11001111b
        db 0x0

    _gdt_user_data: ; 0x20
        dw 0xffff
        dw 0x0
        db 0x0
        db 11110010b
        db 11001111b
        db 0x0

    _gdt_tss: ; 0x28
        dw 0x0000
        dw 0x0
        db 0x0
        db 10001001b
        db 01000000b
        db 0x0

    _gdt_end:

    _gdt_desc:
        dw _gdt_end - _gdt_begin - 1
        dd _gdt_begin

    _tss_begin:
        ; See http://wiki.osdev.org/Task_State_Segment. For the most part,
        ; everything documented is the register name, and everything not
        ; documented is reserved.
        dw 0x0 ;LINK
        dw 0x0
        dd 0x0 ;ESP0
        dw 0x0 ;SS0
        dw 0x0
        dd 0x0 ;ESP1
        dw 0x0 ;SS1
        dw 0x0
        dd 0x0 ;ESP2
        dw 0x0 ;SS2
        dw 0x0
        dd 0x0 ;CR3
        dd 0x0 ;EIP
        dd 0x0 ;EFLAGS
        dd 0x0 ;EAX
        dd 0x0 ;ECX
        dd 0x0 ;EDX
        dd 0x0 ;EBX
        dd 0x0 ;ESP
        dd 0x0 ;EBP
        dd 0x0 ;ESI
        dd 0x0 ;EDI
        dw 0x0 ;ES
        dw 0x0
        dw 0x0 ;CS
        dw 0x0
        dw 0x0 ;SS
        dw 0x0
        dw 0x0 ;DS
        dw 0x0
        dw 0x0 ;FS
        dw 0x0
        dw 0x0 ;GS
        dw 0x0
        dw 0x0 ;LDTR
        dw 0x0
        dw 104 ;IOPB offset (the sizeof the TSS)
    _tss_end:
