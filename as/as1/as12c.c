/* translated from as12.s
error: as12.s, as13.s, as14.s, as15.s, as16.s, as17.s
betwen: as12.s, as14.s, as16.s, as17.s
putw: as12.s, as14.s, as15.s
*/

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
