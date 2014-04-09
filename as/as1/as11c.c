/* translated from as11.s */

int outbuf[];
char atmp1[], atmp2[], atmp3[];
char errflg, pof, fbfil;
char *usymtab, *symend, *memend;
char *unglob "-g";

go()
{
	int fp;

	usymtab = symend = memend = sbrk(0);

	/* as2�ֈ����p���ꎞ�t�@�C�����쐬 */
	pof   = fcreat(atmp1);
	fbfil = fcreat(atmp2);
	fp    = fcreat(atmp3);

	assem();

	/* �o�̓o�b�t�@���t���b�V�� */
	write(pof, outbuf, 512);

	/* �V���{���e�[�u�����_���v */
	write(fp, usymtab, symend - usymtab);

	/* �t�@�C������� */
	close(fp);
	close(fbfil);
	close(pof);

	/* �G���[���������Ă���ΏI�� */
	if (errflg) aexit(); 

	execl("/lib/as2", "/lib/as2", atmp1, atmp2, atmp3, unglob, 0);
	filerr("lib/as2", "?\n");
	exit(1);
}

aexit()
{
	unlink(atmp1);
	unlink(atmp2);
	unlink(atmp3);	
	exit(errflg);
}

filerr(fname, msg)
char *fname, *msg;
{
	printf("%s%s", fname, msg);
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
