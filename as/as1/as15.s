/
/

/ a5 -- pdp-11 assembler pass 1

.globl _rname
_rname:
	mov r5, -(sp)
	mov 4(sp), r0
	jsr pc, _rname_
	mov r4, r0
	mov (sp)+, r5
	rts pc

_rname_:
	jsr pc, rname

.globl _number
_number:
	jsr pc, number
		br 1f
	mov r0, *2(sp)
	mov r4, r0
	rts pc
1:
	mov r0, *2(sp)
	mov $1, r0
	rts pc

readop:
	jsr pc, _readop
	mov r0, r4
	rts pc
