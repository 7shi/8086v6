/* translated from as22.s */

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

/* for outw */
char usymtab[];
int xsymbol;
int dotdot;


outw(r2, r3)
int r2;
int r3;
{
	char c_flg;
	char r3_flg;
	
	if(dot[-1] == 4) {
		error("x");
		return;
	}

	if(dot[0] & 1) {
		error("o");
		outb(r2, 0);		
		return;
	}

	r3_flg = 1;

	dot[0] =+ 2;
	
	if(passno[0] == 0) {
		return;
	}

	c_flg = (r3 >> 15) & 1;
	r3 =<< 1;
	r3 =>> 1;
	

	if(r3 != 040) {
		r3 =& ~040;
		if((r3 >= 0) && (r3 < 5)) {
			r3_flg = 0;
		} else if(r3 == 033) {
			error("r");
			r3 = 1;
			r3_flg = 0;
		} else if(r3 != 034) {
			r3 = 1;
			r3_flg = 0;
		}
	}


	if(r3_flg) {
		outmod = 0666;
		r3 = xsymbol;
		r3 =- &usymtab;
		r3 =<< 1;
		r3 =| 4;

		r3 =<< 1;
		r3 =| c_flg;
		putw(r2, &txtp);
		*tseekp =+ 2;
		putw(0, &relp);
		*rseekp =+ 2;
		return;
	}

	if((r3 >= 0) && ((r3 != 2) || (r3 != 3))) {
		if(c_flg != 0) {
			r2 =- dotdot;
		}
	} else if(c_flg == 0) {
		r2 =+ dotdot;
	}


	r3 = (--r3 < 0) ? 0 : r3;

	r3 =<< 1;
	r3 =| c_flg;
	putw(r2, &txtp);
	*tseekp =+ 2;
	putw(0, &relp);
	*rseekp =+ 2;

	return;

}








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
