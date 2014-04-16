/
/

/  a7 -- pdp-11 assembler

expres:
	mov r3, -(sp)
	mov sp, r3
	mov r2, -(sp)
	mov sp, r2
	mov r3, -(sp)
	mov r2, -(sp)
	mov r4, -(sp)
	jsr pc, _expres
	add $6, sp
	mov (sp)+, r2
	mov (sp)+, r3
	mov r0, r4
	rts pc
