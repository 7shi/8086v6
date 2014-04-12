/
/

/ a4 -- pdp-11 assembler pass 2

oset:
	mov	r2,-(sp)
	mov	(r5)+,r1
	mov	r0,r2
	mov r2,-(sp)
	mov r1,-(sp)
	mov r0,-(sp)
	jsr pc, _oset
	tst (sp)+
	tst (sp)+
	mov (sp)+,r2
	mov r0, r1
	mov	(sp)+,r2
	rts	r5

putw:
	mov	r1,-(sp)
/	mov r0, -(sp)
/	mov $'0, -(sp)
/	jsr pc, _debug8
/	tst (sp)+
/	mov (sp)+, r0
	mov	r2,-(sp)
	mov	(r5)+,r2
	mov	(r2)+,r1	/ slot
	cmp	r1,(r2)		/ buf max
	bhis	1f
	mov	r0,(r1)+
	mov	r1,-(r2)
	br	2f
1:
	tst	(r2)+
	mov	r0,-(sp)
	jsr	r5,flush1
	mov	(sp)+,r0
	mov	r0,*(r2)+
	add	$2,-(r2)
2:
	mov	(sp)+,r2
	mov	(sp)+,r1
	rts	r5

flush:
	mov	(r5)+,r2
	cmp	(r2)+,(r2)+
flush1:
	mov	(r2)+,r1
	mov	r1,0f		/ seek address
	mov	fout,r0
	sys	indir; 9f
	.data
9:	sys	seek; 0:..; 0
	.text
	bic	$!777,r1
	add	r2,r1		/ write address
	mov	r1,0f
	mov	r2,r0
	bis	$777,-(r2)
	inc	(r2)		/ new seek addr
	cmp	-(r2),-(r2)
	sub	(r2),r1
	neg	r1
	mov	r1,0f+2		/ count
	mov	r0,(r2)		/ new next slot
	mov	fout,r0
	sys	indir; 9f
	.data
9:	sys	write; 0:..; ..
	.text
	rts	r5

readop:
	mov r0, -(sp)
	mov r1, -(sp)
	jsr pc, _readop
	mov (sp)+, r1
	mov r0, r4
	mov (sp)+, r0
	rts pc	

getw:
	mov r1, -(sp)
	tst -(sp)
	mov sp, r0
	mov r0, -(sp)
	jsr pc, _getw
	tst (sp)+
	mov (sp)+, r4
	mov (sp)+, r1
	tst r0
	beq 0f
	sev
0:
	rts	pc

getw1:
	mov r1, -(sp)
	tst -(sp)
	mov sp, r0
	mov r0, -(sp)
	jsr pc, _getw1
	tst (sp)+
	mov (sp)+, r4
	mov (sp)+, r1
	tst r0
	beq 0f
	sev
0:
	rts pc

