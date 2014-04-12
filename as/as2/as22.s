/
/

/ a2 -- pdp-11 assembler pass 2

/ wrapper functions

.data

.globl _putw
_putw:
	mov 2(sp), r0
	mov 4(sp), 0f
	jsr r5, putw; 0:.
	rts pc

.text

outw:
	mov r1, -(sp)
	mov r3, -(sp)
	mov r2, -(sp)
	jsr pc, _outw
	cmp (sp)+, (sp)+
	mov (sp)+, r1
	rts pc

outb:
	mov r1, -(sp)
	mov r3, -(sp)
	mov r2, -(sp)
	jsr pc, _outb
	cmp (sp)+, (sp)+
	mov (sp)+, r1
	rts pc

error:
	mov r3, -(sp)
	mov r2, -(sp)
	mov r1, -(sp)
	mov r0, -(sp)
	mov r5, -(sp)
	jsr pc, _error
	tst (sp)+
	mov (sp)+, r0
	mov (sp)+, r1
	mov (sp)+, r2
	mov (sp)+, r3
	tst (r5)+
	rts	r5

betwen:
	mov r1, -(sp)
	mov r5, -(sp)
	mov r0, -(sp)
	jsr pc, _betwen
	cmp (r5)+, (r5)+
	add r0, r5
	add r0, r5
	mov (sp)+, r0
	tst (sp)+
	mov (sp)+, r1
	rts r5
