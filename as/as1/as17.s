/
/

/  a7 -- pdp-11 assembler pass 1

/ input: r4
expres:
	mov r0, -(sp)
	mov r1, -(sp)
	tst -(sp) / -> r2
	mov sp, r1
	tst -(sp) / -> r3
	mov sp, r0
	mov r0, -(sp)
	mov r1, -(sp)
	mov r4, -(sp)
	jsr pc, _expres
	add $6, sp
	mov r0, r4
	mov (sp)+, r3
	mov (sp)+, r2
	mov (sp)+, r1
	mov (sp)+, r0
	rts pc
