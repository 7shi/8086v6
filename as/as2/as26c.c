/* translated from as26.s */

checkreg(r1, r2, r3)
int *r2, *r3;
{
    if (*r2 > 7 || (r1 > 1 && *r3 < 5)) {
        error("a");
        r2 = r3 = 0;
    }
}

checkrp(r4)
{
    if (r4 == ')') return readop();
    error(")");
    return r4;
}

int brtabp, brlen, brdelt, dot;
char brtab[];

setbr(r0)
{
    int r1;
    r1 = brtabp;
    if (r1 >= brlen) return 2;
    ++brtabp;
    r0 =- dot;
    if (r0 > 0) r0 =- brdelt;
    if (-254 <= r0 && r0 <= 256) return 0;
    brtab[r1 >> 3] =| 1 << (r1 & 7);
    return 2;
}

getbr()
{
    int r1, tmp;
    r1 = brtabp;
    if (r1 >= brlen) return 1;
    tmp = r1 & 7;
    ++brtabp;
    r1 = brtab[r1 >> 3];
    return (r1 >> tmp) & 1; /* 0-bit into c-bit */
}
