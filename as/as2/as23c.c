/* translated from as23.s */

int curfb[], nxtfb[], *fbbufp;

fbadv(r4)
{
    int *r1;
    r1 = nxtfb[r4];
    curfb[r4] = r1;
    if (r1 == 0) {
        r1 = fbbufp - 2;
    }
    do {
        r1 =+ 2;
        if (*r1 >> 9 == r4) break;
    } while (*r1 >= 0);
    nxtfb[r4] = r1;
}
