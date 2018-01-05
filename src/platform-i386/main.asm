; asmsyntax=nasm

extern panic_stack_dump_hex
global stack_dump

stack_dump:
	push ebp
	mov ebp, esp
	call panic_stack_dump_hex
	pop ebp
	ret
