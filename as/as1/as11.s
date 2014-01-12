/
/

/ PDP-11 assembler pass 0

indir	= 0

	/jmp	start
go:
	jsr	pc,assem
	movb	pof,r0
	sys	write; outbuf; 512.
	movb	pof,r0
	sys	close
	movb	fbfil,r0
	sys	close
	tstb	errflg
    bne aexit
	jsr	r5,fcreat; _atmp3
	mov	r0,r1
	mov	symend,0f
	sub	$usymtab,0f
	sys	indir; 9f
	.data
9:	sys	write; usymtab; 0:..
	.text
	mov	r1,r0
	sys	close
	sys	exec; 2f; 1f
	mov	$2f,r0
	jsr	r5,filerr; "?\n

aexit:
    jmp _aexit

.data
1:
	2f
	_atmp1
	_atmp2
	_atmp3
.globl _unglob; _unglob: unglob:
	3f
	0
	.text
2:
fpass2:
	</lib/as2\0>
3:
	<-g\0>
	.even

filerr:
    mov r1, -(sp)
    mov r5, -(sp)
    mov r0, -(sp)
    jsr pc, _filerr
    cmp (sp)+, (sp)+
    mov (sp)+, r1
    tst (r5)+
    rts r5

fcreat:
	mov	r4,-(sp)
	mov	(r5)+,r4
	mov	r4,0f
1:
	sys	indir; 9f
	.data
9:	sys	stat; 0:..; outbuf
	.text
	bec	2f
	mov	r4,0f
	sys	indir; 9f
	.data
9:	sys	creat; 0:..; 444
	.text
	bes	2f
	mov	(sp)+,r4
	rts	r5
2:
	incb	9.(r4)
	cmpb	9.(r4),$'z
	blos	1b
	mov	r4,r0
	jsr	r5,filerr; "?\n
	sys	exit
