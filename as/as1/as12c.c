/* translated from as12.s */

char errflg;
char **curarg;
char fxxxx[] "f xxxx\n";
int line;

error(r5)
char *r5;
{
	int i, ln;
	char *p;
	++errflg;
	if (*curarg) {
		filerr(*curarg, "\n");
		*curarg = 0;
	}
	fxxxx[0] = *r5;
	ln = line;

	/* lineの値を10進数で表示する */
	p = &fxxxx[6];
	for (i = 0; i < 4; i++) {
		*(--p) = '0' + (ln % 10);
		ln =/ 10;
	}
	write(1, fxxxx, 7);
}

int ifflg, obufi, outbuf[];
char pof;

putw(r4)
{
	if (!ifflg || r4 == '\n') {
		outbuf[obufi++] = r4;
		if (obufi >= 256) {
			write(pof, outbuf, 512);
			obufi = 0;
		}
	}
}
