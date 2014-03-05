/* translated from as11.s */

int outbuf[];
char atmp1[], atmp2[], atmp3[];
char errflg, pof, fbfil;
char *usymtab, *symend, *memend;

go()
{
	int fp;
	usymtab = symend = memend = sbrk(0);
	assem();
	write(pof, outbuf, 512);
	close(pof);
	close(fbfil);

	if(errflg != 0) {
		aexit(); 
	}

	/* シンボルテーブルをダンプ */
	fp = fcreat(atmp3);
	write(fp, usymtab, symend - usymtab);
	close(fp);

	execl("/lib/as2", "/lib/as2", atmp1, atmp2, atmp3, "-g");
	filerr("lib/as2", "?\n");
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
