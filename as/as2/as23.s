/
/

/ a3 -- pdp-11 assembler pass 2

.globl _opline
_opline:
	mov r2, -(sp)
	mov r3, -(sp)
	mov r4, -(sp)
	mov r5, -(sp)
	mov 10.(sp), r4
	jsr pc, opline
	mov r4, r0
	mov (sp)+, r5
	mov (sp)+, r4
	mov (sp)+, r3
	mov (sp)+, r2
	rts pc
