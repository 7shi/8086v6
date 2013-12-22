/
/

/ a2 -- pdp-11 assembler pass 1

.data
_filerr:
	mov 4(sp), 0f
	mov 2(sp), r0
	jsr r5, filerr; 0:0
	rts pc

.text
error:
	mov	r0, -(sp)
	mov	r1, -(sp)
	mov r5, -(sp)
	jsr pc, _error
	tst (sp)+
	mov	(sp)+,r1
	mov	(sp)+,r0
	tst (r5)+
	rts	r5

betwen:
	mov r1, -(sp)
	mov r5, -(sp)
	mov r0, -(sp)
	jsr pc, _betwen
	add r0, r5
	add r0, r5
	cmp (r5)+, (r5)+
	mov (sp)+, r0
	tst (sp)+
	mov (sp)+, r1
	rts r5

putw:
	mov r1, -(sp)
	mov r4, -(sp)
	jsr pc, _putw
	tst (sp)+
	mov (sp)+, r1
	rts pc
