/* translated from as16.s */

int* dot;
int* dotrel;
int savdot[];
int savop;
int ifflg;
int numval;

/* using for intptr_t */
struct { char cval; };

opline(r4)
int r4;
{
    int r0, r2, r3, sp;

    if (r4 == '<') {
        *dot =+ numval;
        return readop();
    } else if (0 <= r4 && r4 <= 0200) {
        r4 = expres(r4, &r2, &r3);
        *dot =+ 2;
        return r4;
    }

    r0 = r4->cval;
    if (r0 != 20 && 5 <= r0 && r0 <= 30) r4 = readop();

    switch (r0) {
        case 5: /* map fop freg,fdst to double */
        case 10: /* map fld/fst to double */
        case 11:
        case 12: /* map fop fsrc,freg to double */
        case 24: /* map mul s,r to double */
        case 7:
            /* double */
            r4 = addres(r4, &r0);
            if (r4 != ',') {
                error("a");
                return r4;
            }
            r4 = readop();
        case 13: /* single operand */
            r4 = addres(r4, &r0);
            *dot =+ 2;
            return r4;
        case 14: /* .byte */
            for (;;) {
                r4 = expres(r4, &r2, &r3);
                *dot =+ 1;
                if (r4 != ',') break;
                r4 = readop();
            }
            return r4;
        case 15: /* < (.ascii) */
            *dot =+ numval;
            return readop();
        case 16: /* .even */
            *dot =+ 1;
            *dot =& ~1;
            return r4;
        case 17: /* .if */
            r4 = expres(r4, &r2, &r3);
            if (r3 == 0) error("U");
            if (r2 == 0) ifflg =+ 1;
            return r4;
        case 18: /* endif */
            return r4;
        case 19: /* .globl */
            while (r4 >= 0200) {
                r4->cval =| 040;
                r4 = readop();
                if (r4 != ',') break;
                r4 = readop();
            }
            return r4;
        case 21:
        case 22:
        case 23:
            savdot[*dotrel-2] = *dot;
            *dot = savdot[r0-21];
            *dotrel = r0 - 19;
            return r4;
        case 25: /* sob */
            r4 = expres(r4, &r2, &r3);
            if (r4 != ',') error("a");
            r4 = readop();
            break;
        case 26: /* .common */
            if (r4 >= 0200) {
                r4->cval =| 040;
                r4 = readop();
                if (r4 == ',') {
                    r4 = expres(readop(), &r2, &r3);
                    return r4;
                }
            }
            error("x");
            return r4;
        case 29: /* jbr */
        case 30: /* jeq, etc */
            sp = r0 == 29 ? 4 : 6;
            r4 = expres(r4, &r2, &r3);
            if (r3 == *dotrel) {
                r2 =- *dot;
                if (r2 < 0 && r2 >= -0376) {
                    sp = 2;
                }
            }
            *dot =+ sp;
            return r4;
    }
    r4 = expres(r4, &r2, &r3);
    *dot =+ 2;
    return r4;
}

addres(r4, r0)
int r4;
int *r0;
{
    int r2, r3;

    switch (r4) {
    case '(':
        r4 = expres(readop(), &r2, &r3);
        r4 = checkrp(r4);
        checkreg(r2,r3);
        if (r4 == '+') {
            r4 = readop();
            *r0 = 0;
            return r4;
        }
        *r0 = 2;
        return r4;
    case '-':
        r4 = readop();
        if (r4 != '(') {
            savop = r4;
            r4 = '-';
            return getx(r4);
        }
        r4 = expres(readop(), &r2, &r3);
        r4 = checkrp(r4);
        checkreg(r2, r3);
        *r0 = 0;
        return r4;
    case '$':
        r4 = expres(readop(), &r2, &r3);
        *dot =+ 2;
        *r0 = 0;
        return r4;
    case '*':
        r4 = readop();
        if (r4 == '*') {
            error("*");
        }
        r4 = addres(r4, r0);
        *dot =+ *r0;
        return r4;
    }
    return getx(r4);
}

getx(r4)
int r4;
{
    int r2, r3;

    r4 = expres(r4, &r2, &r3);
    if (r4 == '(') {
        r4 = expres(readop(), &r2, &r3);
        checkreg(r2, r3);
        r4 = checkrp(r4);
        *dot =+ 2;
    } else if (r3 == 20) {
        /* register type */
        checkreg(r2, r3);
    } else {
        *dot =+ 2;
    }
    return r4;
}

checkreg(r2, r3)
int r2;
int r3;
{
    if (r2 <= 7) {
        if (r3 == 1 || r3 > 4) {
            return ;
        }
    }

    error("a");
    return ;
}

checkrp(r4)
int r4;
{
    if (r4 == ')') {
        r4 = readop();
    } else {
        error(")");
    }
    return r4;
}
