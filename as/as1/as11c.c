/* translated from as11.s */
char atmp1[];
char atmp2[];
char atmp3[];

aexit(type)
	 int type;
{
	unlink(atmp1);
	unlink(atmp2);
	unlink(atmp3);
	exit(type);
}
