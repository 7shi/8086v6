/
/

/ a21 -- pdp-11 assembler pass 2 

indir	= 0

/ set up sizes and origins

go:

/ read in symbol table

	mov	$usymtab,r1
1:
	jsr	pc,getw
	bvs	1f
	add	$14,symsiz		/ count symbols
	jsr	pc,getw
	jsr	pc,getw
	jsr	pc,getw
	jsr	pc,getw
	mov	r4,r0
	bic	$!37,r0
	cmp	r0,$2			/text
	blo	2f
	cmp	r0,$3			/data
	bhi	2f
	add	$31,r4			/mark "estimated"
	mov	r4,(r1)+
	jsr	pc,getw
	mov	r4,(r1)+
	br	3f
2:
	clr	(r1)+
	clr	(r1)+
	jsr	pc,getw
3:
	jsr	pc,setbrk
	br	1b
1:

/ read in f-b definitions

	mov	r1,fbbufp
	movb	fbfil,fin
	clr	ibufc
1:
	jsr	pc,getw
	bvs	1f
	add	$31,r4			/ "estimated"
	mov	r4,(r1)+
	jsr	pc,getw
	mov	r4,(r1)+
	jsr	pc,setbrk
	br	1b
1:
	mov	r1,endtable
	mov	$100000,(r1)+

/ set up input text file; initialize f-b table

	jsr	pc,setup
/ do pass 1

	jsr	pc,assem

/ prepare for pass 2
	cmp	_outmod,$777
	beq	1f
	jmp	aexit
1:
	clr	dot
	mov	$2,dotrel
	mov	$..,dotdot
	clr	brtabp
	movb	fin,r0
	sys	close
	jsr	r5,ofile; a.tmp1
	movb	r0,fin
	clr	ibufc
	jsr	pc,setup
	inc	passno
	inc	bsssiz
	bic	$1,bsssiz
	mov	txtsiz,r1
	inc	r1
	bic	$1,r1
	mov	r1,txtsiz
	mov	datsiz,r2
	inc	r2
	bic	$1,r2
	mov	r2,datsiz
.globl _go_
_go_:
mov txtsiz, r1
mov datsiz, r2
	mov	r1,r3
	mov	r3,datbase	/ txtsiz
	mov	r3,savdot+2
	add	r2,r3
	mov	r3,bssbase	/ txtsiz+datsiz
	mov	r3,savdot+4
	asl	r3
	add	$20,r3
	mov	r3,symseek	/ 2*txtsiz+2*datsiz+20
	sub	r2,r3
	mov	r3,drelseek	/ 2*txtsiz+datsiz
	sub	r1,r3
	mov	r3,trelseek	/ txtsiz+datsiz+20
	sub	r2,r3
	mov	r3,datseek	/ txtsiz+20
	mov	$usymtab,r1
1:
	jsr	pc,doreloc
	add	$4,r1
	cmp	r1,endtable
	blo	1b
	clr	r0
	jsr	r5,oset; txtp
	mov	trelseek,r0
	jsr	r5,oset; relp
	mov	$8.,r2
	mov	$txtmagic,r1
1:
	mov	(r1)+,r0
	jsr	r5,putw; txtp
	dec	r2
	bne	1b
	jsr	pc,assem

/polish off text and relocation

	jsr	r5,flush; txtp
	jsr	r5,flush; relp

/ append full symbol table

	mov	symf,r0
	mov	r0,fin
	sys	seek; 0; 0;
	clr	ibufc
	mov	symseek,r0
	jsr	r5,oset; txtp
	mov	$usymtab,r1
1:
	jsr	pc,getw
	bvs	1f
	mov	r4,r0
	jsr	r5,putw; txtp
	jsr	pc,getw
	mov	r4,r0
	jsr	r5,putw; txtp
	jsr	pc,getw
	mov	r4,r0
	jsr	r5,putw; txtp
	jsr	pc,getw
	mov	r4,r0
	jsr	r5,putw; txtp
	mov	(r1)+,r0
	jsr	r5,putw; txtp
	mov	(r1)+,r0
	jsr	r5,putw; txtp
	jsr	pc,getw
	jsr	pc,getw
	br	1b
1:
	jsr	r5,flush; txtp
	jmp	aexit

aexit:
	jmp _aexit

filerr:
	mov *(r5), -(sp)
	jmp _filerr

doreloc:
	mov r1, -(sp)
	jsr pc, _doreloc
	mov (sp)+, r1
	rts pc

setbrk:
	mov r1, -(sp)
	jsr pc, _setbrk
	mov (sp)+, r1
	rts pc

setup:
	jmp _setup

ofile:
	mov *(r5)+, -(sp)
	jsr pc, _ofile
	tst (sp)+
	rts r5

.globl _assem
_assem:
	jmp assem

.globl _fbadv
_fbadv:
	mov 2(sp), r4
	jmp fbadv
