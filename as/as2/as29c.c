/* translated from as29.s */

int defund;
char *atmp1, *atmp2, *atmp3;
char txtfil, fbfil, symf, fin, fout;
char aout[], *aoutp;
aexit();

main(argc, argv)
int argc;
char *argv[];
{
	if (!(signal(2, 1) & 1))
		signal(2, aexit);
	if (argc < 4)
		aexit();
	if (argc >= 5)
		/* globalize all undefineds */
		defund = 040;
	atmp1 = argv[1];
	atmp2 = argv[2];
	atmp3 = argv[3];
	txtfil     = ofile(atmp1);
	fbfil      = ofile(atmp2);
	symf = fin = ofile(atmp3);
	if ((fout = creat(aout, 0)) < 0)
		filerr(aoutp);
	go();
}
