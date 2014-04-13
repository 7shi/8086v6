/* translated from as21.s */

int errflg;
int outmod 0777;
char *atmp1, *atmp2, *atmp3, aout[];

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    chmod(aout, outmod);
    exit(errflg);
}

char ch;
int qnl;

filerr(r5)
char *r5;
{
    if (!errflg) ++errflg;
    write(1, r5, strlen(r5));
    write(1, &qnl, 2);
    aexit();
}

int defund, datbase, bssbase;

doreloc(r1)
int *r1;
{
    int r0;
    if (!(r0 = r1[0])) r1[0] =| defund;
    r0 =& 31;
    if (r0 == 3) {
        r1[1] =+ datbase;
    } else if (r0 == 4) {
        r1[1] =+ bssbase;
    }
}

char end[];
char *memend end;

setbrk(r1)
char *r1;
{
    if (r1 + 16 >= memend) {
        memend =+ 512;
        brk(memend);
    }
}

int curfb[], ibufc;
char txtfil, fin;

setup()
{
    int i;
    memset(curfb, 0, 40);
    fin = txtfil;
    ibufc = 0;
    for (i = 0; i < 10; ++i) {
        fbadv(i);
    }
}
