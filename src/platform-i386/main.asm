; asmsyntax=nasm

extern flail_stack_dump_hex
global flail_stack_dump
global flail_wait_forever

flail_stack_dump:
    push ebp
    mov ebp, esp
    call flail_stack_dump_hex
    pop ebp
    ret

flail_wait_forever:
    cli
    hlt
    jmp flail_wait_forever
