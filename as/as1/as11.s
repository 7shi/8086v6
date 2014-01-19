/
/

/ PDP-11 assembler pass 0

indir	= 0

aexit:
    jmp _aexit

filerr:
    mov r1, -(sp)
    mov r5, -(sp)
    mov r0, -(sp)
    jsr pc, _filerr
    cmp (sp)+, (sp)+
    mov (sp)+, r1
    rts r5

fcreat:
    mov r1, -(sp)
	mov (r5)+, -(sp)
	jsr pc, _fcreat
	tst (sp)+
    mov (sp)+, r1
    rts r5
