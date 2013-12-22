/* translated from as12.s
error: as12.s, as13.s, as14.s, as15.s, as16.s, as17.s
betwen: as12.s, as14.s, as16.s, as17.s
putw: as12.s, as14.s, as15.s
*/

/*
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
*/

char errflg;
char **curarg;
char fxxx[] "f xxxx\n";
int line;

error(r5)
char *r5;
{
	int i, ln;
	char *p;
	++errflg;
	if (*curarg) {
		filerr(*curarg, '\n');
		*curarg = 0;
	}
	fxxx[0] = *r5;
	ln = line;
	p = &fxxx[6];
	for (i = 0; i < 4; i++) {
		*(--p) = '0' + (ln % 10);
		ln =/ 10;
	}
	write(1, fxxx, 7);
}

/*
betwen:
	cmp	r0,(r5)+
	blt	1f
	cmp	(r5)+,r0
	blt	2f
1:
	tst	(r5)+
2:
	rts	r5

save r0 and r1
like syscall fork
[as14.s]
	jsr	r5,betwen; '0; '9
		br 1f
-> if '0' <= r0 <= '9' skip "br 1f"
*/

betwen(r0, r5)
int *r5;
{
	return r5[0] <= r0 && r0 <= r5[1];
}

/*
putw:
	tst	ifflg
	beq	1f
	cmp	r4,$'\n
	bne	2f
1:
	mov	r4,*obufp
	add	$2,obufp
	cmp	obufp,$outbuf+512.
	blo	2f / bcs
	mov	$outbuf,obufp
	movb	pof,r0
	sys	write; outbuf; 512.
2:
	rts	pc
*/

int ifflg;
int *obufp;
char outbuf[512];
char pof;

putw(r4)
{
	if (!ifflg || r4 == '\n') {
		*(obufp++) = r4;
		if (obufp >= &outbuf[512]) {
			obufp = outbuf;
			write(pof, outbuf, 512);
		}
	}
}
