/* translated from as11.s */

int outmod, passno, errflg;
char atmp1[], atmp2[], atmp3[], *aout;

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    if (passno) chmod(aout, outmod);
    exit(errflg);
}

fcreat(atmp)
char *atmp;
{
    int ret, st[20];
    do {
        if(stat(atmp, st) < 0) {
            ret = creat(atmp, 0444);
            if(ret > 0) return ret;
        }
    } while (++atmp[9] <= 'z');
    filerr(atmp, "?");
    exit(1);
}
