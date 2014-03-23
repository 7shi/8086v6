/* translated from as22.s */


/* for debug */
char buf[8]  " 000000\n";
showoct(cal, val)
int cal;
{
        register int c;
        char *p;        
        int i;
        /*      c = 65535;*/
        c = val;

        p = &buf[7];
        for(i = 0; i < 6; i++) {
                if(i == 5) {
                        *(--p) = '0' + (c & 1); 
                } else {
                        *(--p) = '0' + (c & 7);
                }
                c =>> 3;
        }
        
        write(1, buf, 8);
}



int outmod;
char argb[];
char fxxxx[] "f xxxx\n";
int line;

/* for outb */
int dot[];
char passno[];
char *txtp[];
char *relp[];
int *rseekp;
int *tseekp;

outb(r2, r3)
int r2;
int r3;
{
	char *txtpp;
	/* r3は1でOK */
	/* dot[-1]は3でOK */
	/* passno[0] は0か1*/
	/* r2は1 */

	if(dot[-1] == 4) { 
		error("x");
		return;
	}
	if(!(r3 <= 1)) error("r");

	if(passno[0] != 0) {
		if(dot[0] & 1) {
			txtpp = txtp[0]; 
			*(--txtpp) = r2 & 0377;
		} else {
			putw(r2, &txtp);
			putw(0, &relp);
			*rseekp =+ 2;
			*tseekp =+ 2;

		}
	}
	++dot[0];  /* inc dot, rts pc */
}




error(r5)
char *r5;
{
	int i, ln;
	char *p;

	/* outmodを666にする */
	outmod = 0666;

	/* argbの内容を書き出し，終了を0を書き込む */
	for(i = 0; argb[i]; i++);
	write(1, argb, i);
	for(i = 0; argb[i]; i++) argb[i] = 0;

	fxxxx[0] = *r5;
	ln = line;

	/* line[0]の内容を10進数で表示する */
	p = &fxxxx[6];
	for (i = 0; i < 4; i++) {
		*(--p) = '0' + (ln % 10);
		ln =/ 10;
	}
	write(1, fxxxx, 7);
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
