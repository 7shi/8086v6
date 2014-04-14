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

.globl _expres
_expres:
	mov r2, -(sp)
	mov r3, -(sp)
	mov r4, -(sp)
	mov r5, -(sp)
	mov 10.(sp), r4
	jsr pc, expres
	mov r4, r0
	mov r3, *14.(sp)
	mov r2, *12.(sp)
	mov (sp)+, r5
	mov (sp)+, r4
	mov (sp)+, r3
	mov (sp)+, r2
	rts pc
