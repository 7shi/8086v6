/
/

/ a5 -- pdp-11 assembler pass 1

readop:
	jsr pc, _readop
	mov r0, r4
	rts pc
