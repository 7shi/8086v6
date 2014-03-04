/
/

/ a3 -- pdp-11 assembler pass 1

.globl _opline
_opline:
	mov r5, -(sp)
	mov 4(sp), r4
	jsr pc, opline
	mov r4, r0
	mov (sp)+, r5
	rts pc

fbcheck:
	mov r1, -(sp)
	mov r0, -(sp)
	jsr pc, _fbcheck
	tst (sp)+
	mov (sp)+, r1
	rts pc
