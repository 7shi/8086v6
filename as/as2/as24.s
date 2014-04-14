/
/

/ a4 -- pdp-11 assembler pass 2

oset:
	mov (r5)+, -(sp)
	mov r0, -(sp)
	jsr pc, _oset
	cmp (sp)+, (sp)+
	rts r5

putw:
	mov r1, -(sp)
	mov (r5)+, -(sp)
	mov r0, -(sp)
	jsr pc, _putw
	cmp (sp)+, (sp)+
	mov (sp)+, r1
	rts r5

flush:
	mov (r5)+, -(sp)
	jsr pc, _flush
	tst (sp)+
	rts r5

readop:
	mov r1, -(sp)
	jsr pc, _readop
	mov r0, r4
	mov (sp)+, r1
	rts pc	

getw:
	mov r1, -(sp)
	jsr pc, _getw
	mov r0, r4
	mov (sp)+, r1
	rts pc
