/
/

/ a21 -- pdp-11 assembler pass 2 

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
