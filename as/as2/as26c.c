/* translated from as26.s */

int xsymbol, dot, savop, adrbuf[];

addres(r4, /*in,out*/r5, /*out*/r2)
int **r5, *r2;
{
    return addres1(r4, 0, r5, r2);
}

addres1(r4, tmp, /*in,out*/r5, /*out*/r2)
int **r5, *r2;
{
    int r1, r3;
    switch (r4) {
    case '(':
        r4 = expres(readop(), r2, &r3);
        r4 = checkrp(r4);
        checkreg(r2, &r3);
        if (r4 == '+') {
            r4 = readop();
            *r2 =| 020;
            *r2 =| tmp;
        } else if (tmp) {
            *r2 =| 070;
            *((*r5)++) = 0;
            *((*r5)++) = 0;
            *((*r5)++) = xsymbol;
        } else {
            *r2 =| 010;
        }
        return r4;
    case '-':
        r4 = readop();
        if (r4 != '(') {
            savop = r4;
            r4 = '-';
            break;
        }
        r4 = expres(readop(), r2, &r3);
        r4 = checkrp(r4);
        checkreg(r2, &r3);
        *r2 =| tmp;
        *r2 =| 040;
        return r4;
    case '$':
        r4 = expres(readop(), r2, &r3);
        *((*r5)++) = *r2;
        *((*r5)++) = r3;
        *((*r5)++) = xsymbol;
        *r2 = tmp;
        *r2 =| 027;
        return r4;
    case '*':
        if (tmp) error("*");
        return addres1(readop(), 010, r5, r2);
    }
    r4 = expres(r4, r2, &r3);
    if (r4 == '(') {
        r4 = readop();
        *((*r5)++) = *r2;
        *((*r5)++) = r3;
        *((*r5)++) = xsymbol;
        r4 = expres(r4, r2, &r3);
        checkreg(r2, &r3);
        r4 = checkrp(r4);
        *r2 =| 060;
        *r2 =| tmp;
    } else if (r3 == 20) {
        checkreg(r2, &r3);
        *r2 =| tmp;
    } else {
        r3 =| 0100000;
        *r2 =- dot;
        *r2 =- 4;
        if (*r5 != adrbuf) *r2 =- 2;
        *((*r5)++) = *r2; /* index */
        *((*r5)++) =  r3; /* index reloc. */
        *((*r5)++) = xsymbol; /* index global */
        *r2 = 067; /* address mode */
        *r2 =| tmp;
    }
    return r4;
}

checkreg(r2, r3)
int *r2, *r3;
{
    if (*r2 > 7 || (*r2 > 1 && *r3 < 5)) {
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

int brtabp, brlen, brdelt;
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
