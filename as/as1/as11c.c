/* translated from as11.s */
char atmp1[];
char atmp2[];
char atmp3[];

char errflg;

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
