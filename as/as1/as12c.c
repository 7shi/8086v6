/* translated from as12.s
error: as12.s, as13.s, as14.s, as15.s, as16.s, as17.s
betwen: as12.s, as14.s, as16.s, as17.s
putw: as12.s, as14.s, as15.s
*/

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

betwen(atr5, r0, at2r5) {
	return atr5 <= r0 && r0 <= at2r5;
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
