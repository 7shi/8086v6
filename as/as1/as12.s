/
/

/ a2 -- pdp-11 assembler pass 1

error:
	incb	errflg
	mov	r0,-(sp)
	mov	r1,-(sp)
	mov	(r5)+,r0
	tst	*curarg
	beq	1f
	mov	r0,-(sp)
	mov	*curarg,r0
	clr	*curarg
	jsr	r5,filerr; '\n
	mov	(sp)+,r0
1:
	mov	r2,-(sp)
	mov	r3,-(sp)
	mov	line,r3
	movb	r0,1f
	mov	$1f+6,r0
	mov	$4,r1
2:
	clr	r2
	dvd	$10.,r2
	add	$'0,r3
	movb	r3,-(r0)
	mov	r2,r3
	sob	r1,2b
	mov	$1,r0
	sys	write; 1f; 7
	mov	(sp)+,r3
	mov	(sp)+,r2
	mov	(sp)+,r1
	mov	(sp)+,r0
	rts	r5

	.data
1:	<f xxxx\n>
	.even
	.text

betwen:
	mov r1, -(sp)
	mov 2(r5), -(sp)
	mov r0, -(sp)
	mov (r5), -(sp)
	jsr pc, _betwen
	asl r0 / r0 =<< 1;
	add $4, r0
	add r0, r5
	tst (sp)+
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
