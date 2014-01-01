/* translated from as12.s */

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
		filerr(*curarg, " \n");
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

/* betwen
戻り先をずらすことで条件判定を行っている。
C言語からは使わずにインラインで条件判定を書いた方が良い。
【例】
jsr r5, betwen; '0; '9
    br 1f
     ↓
if (r0 < '0' || '9' < r0) goto 1f;
*/

betwen(r0, r5)
int *r5;
{
	return r5[0] <= r0 && r0 <= r5[1];
}

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
