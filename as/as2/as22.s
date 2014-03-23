/
/

/ a2 -- pdp-11 assembler pass 2

outw:
	cmp	dot-2,$4
	beq	9f
	bit	$1,dot
	bne	1f
	add	$2,dot
	tstb	passno
	beq	8f
	clr	-(sp)
	rol	r3
	adc	(sp)
	asr	r3		/ get relative pc bit
	cmp	r3,$40
	bne	2f
/ external references
	mov	$666,outmod		/ make nonexecutable
	mov	xsymbol,r3
	sub	$usymtab,r3
	asl	r3
	bis	$4,r3		/ external relocation
	br	3f
2:
	bic	$40,r3		/ clear any ext bits
	cmp	r3,$5
	blo	4f
	cmp	r3,$33		/ est. text, data
	beq	6f
	cmp	r3,$34
	bne	7f
6:
	jsr	r5,error; 'r
7:
	mov	$1,r3		/ make absolute
4:
	cmp	r3,$2
	blo	5f
	cmp	r3,$4
	bhi	5f
	tst	(sp)
	bne	4f
	add	dotdot,r2
	br	4f
5:
	tst	(sp)
	beq	4f
	sub	dotdot,r2
4:
	dec	r3
	bpl	3f
	clr	r3
3:
	asl	r3
	bis	(sp)+,r3
	mov	r2,r0
	jsr	r5,putw; txtp
	add	$2,*tseekp
	mov	r3,r0
	jsr	r5,putw; relp
	add	$2,*rseekp
8:
	rts	pc
1:
	jsr	r5,error; 'o
	clr	r3
	jsr	pc,outb
	rts	pc

9:
	jsr	r5,error; 'x
	rts	pc

_org_outb:
/   test for r3 and dot-2
/    mov r3, -(sp)    r3 -> 1
/	mov $1, -(sp)
/	jsr pc, _showoct
/	cmp (sp)+, (sp)+
/	mov dot-2, -(sp)  / dot-2 -> 3
/	mov $1, -(sp)
/	jsr pc, _showoct
/	cmp (sp)+, (sp)+

	cmp	dot-2,$4		/ test bss mode
	beq	9b
	cmp	r3,$1
	blos	1f
	jsr	r5,error; 'r
1:
/ test for passno
/ passno is 0 or 1
/    mov passno, -(sp)
/	mov $1, -(sp)
/	jsr pc, _showoct
/	cmp (sp)+, (sp)+


	tstb	passno
	beq	2f
	/ debug for dot
/	mov dot, -(sp)
/	mov $1, -(sp)
/	jsr pc, _showoct
/	cmp (sp)+, (sp)+
	/ debug for dot

	mov	r2,r0
	bit	$1,dot
	bne	1f

    / branch check
	mov $0, -(sp)
	mov $1, -(sp)
	jsr pc, _showoct
	cmp (sp)+, (sp)+
	/end of branch check

	jsr	r5,putw; txtp
	clr	r0
	jsr	r5,putw; relp
	add	$2,*rseekp
	add	$2,*tseekp
	br	2f
1:
    / branch check
	mov $11, -(sp)
	mov $1, -(sp)
	jsr pc, _showoct
	cmp (sp)+, (sp)+
	/end of branch check

	mov	txtp,r0
	movb	r2,-1(r0)
2:
	inc	dot
	rts	pc


/ wrapper function

.data

.globl _putw
_putw:
	mov 2(sp), r0
	mov 4(sp), 0f
	jsr r5, putw; 0:.
	rts pc

.text

outb:
	mov r1, -(sp)
	mov r3, -(sp)
	mov r2, -(sp)
	jsr pc, _outb
	cmp (sp)+, (sp)+
	mov (sp)+, r1
	rts pc

error:
	mov r3, -(sp)
	mov r2, -(sp)
	mov r1, -(sp)
	mov r0, -(sp)
	mov r5, -(sp)
	jsr pc, _error
	tst (sp)+
	mov (sp)+, r0
	mov (sp)+, r1
	mov (sp)+, r2
	mov (sp)+, r3
	tst (r5)+
	rts	r5

betwen:
	mov r1, -(sp)
	mov r5, -(sp)
	mov r0, -(sp)
	jsr pc, _betwen
	cmp (r5)+, (r5)+
	add r0, r5
	add r0, r5
	mov (sp)+, r0
	tst (sp)+
	mov (sp)+, r1
	rts r5
