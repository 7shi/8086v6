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
