/
/

/ a21 -- pdp-11 assembler pass 2 

.globl _go_
_go_:
	mov	txtsiz,r1
	inc	r1
	bic	$1,r1
	mov	r1,txtsiz
	mov	datsiz,r2
	inc	r2
	bic	$1,r2
	mov	r2,datsiz
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
	mov	usymtab,r1
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
jsr pc, _go__

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
