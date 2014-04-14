/
/

/ a21 -- pdp-11 assembler pass 2 

aexit:
	jmp _aexit

filerr:
	mov *(r5), -(sp)
	jmp _filerr

doreloc:
	mov r1, -(sp)
	jsr pc, _doreloc
	mov (sp)+, r1
	rts pc

setbrk:
	mov r1, -(sp)
	jsr pc, _setbrk
	mov (sp)+, r1
	rts pc

setup:
	jmp _setup

ofile:
	mov *(r5)+, -(sp)
	jsr pc, _ofile
	tst (sp)+
	rts r5

.globl _assem
_assem:
	mov r2, -(sp)
	mov r3, -(sp)
	mov r4, -(sp)
	mov r5, -(sp)
	jsr pc, assem
	mov (sp)+, r5
	mov (sp)+, r4
	mov (sp)+, r3
	mov (sp)+, r2
	rts pc
