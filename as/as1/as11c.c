/* translated from as11.s */
char atmp1[];
char atmp2[];
char atmp3[];

char errflg;
char *outbuf;
char pof;
char fbfil;
char *symend;
char usymtab[];

char sdebug8[] " 000000\n";

debug8(str, val) char *str; {
	register int i, v;
	register char *p;
	for (i = 0; str[i]; ++i);
	write(1, str, i);
	v = val;
	p = &sdebug8[7];
	for (i = 0; i < 6; i++) {
		*--p = '0' + (v & 7);
		v =>> 3;
	}
	write(1, sdebug8, 8);
}

go()
{
	int i;  /* for debug */

	int fp;
	assem();
	write(pof, outbuf, 512);
	close(pof);
	close(fbfil);

	if(errflg != 0) {
		aexit(); 
	}

	fp = fcreat(atmp3);
	
	write(1, atmp3, 10);
	write(1, "\n\n\n", 3);
	write(1, fp + '0', 1);
	write(1, "\n\n\n", 3);
	debug8("symend", symend);
	debug8("usymtab", usymtab);
	debug8("symend - usymtab", symend - usymtab);
	write(1, "\n\n\n", 3);

	write(fp, usymtab, (symend - usymtab));
	close(fp);

	/*
	execl("/lib/as2", "/lib/as2", atmp1, atmp2, atmp3, "-g");
	filerr("lib/as2", "?\n");
	*/
}


aexit()
{
	unlink(atmp1);
	unlink(atmp2);
	unlink(atmp3);	
	exit(errflg);
}



filerr(r0, r5)
char *r0;
char *r5;
{
	int i;
	for(i = 0; r0[i] != 0; i++);
	write(1, r0, i);
	write(1, r5, 2);
}


fcreat(r4)
char *r4;
{
	int ret;
	do {
		if(stat(r4, outbuf) < 0) {
			ret = creat(r4, 0444);
			if(ret > 0) {
				return ret;
			}
		}
		++r4[9];		
	} while(r4[9] <= 'z');

	filerr(r4, "?\n");
	exit(1);
}
