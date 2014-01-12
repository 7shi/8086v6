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
    rts r5

fcreat:
    mov r1, -(sp)
	mov (r5)+, -(sp)
	jsr pc, _fcreat
	tst (sp)+
    mov (sp)+, r1
    rts r5
