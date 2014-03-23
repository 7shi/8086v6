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

    r0 = r4;
    if (0 <= r0 && r0 <= 0200) {
        if (r0 == '<') {
            goto opl17;
        }
xpr:
        r4 = expres(r4, &r2, &r3);
        *dot =+ 2;
        return r4;
    }

    /* 1: */
    r0 = r4->cval;
    if (r0 == 024) {
        goto xpr;
    }

    /* 036(base 8) -> 30(base 10) */
    if (r0 < 5 || 036 < r0) {
        goto xpr;
    }

    r4 = readop();
    r0 =<< 1;
 
    switch (r0-10) {
        case 0:
            goto opl13;
        case 2:
            goto opl6;
        case 4:
            goto opl7;
        case 6:
            goto opl10;
        case 8:
            goto opl11;
        case 10:
            goto opl13;
        case 12:
            goto opl13;
        case 14:
            goto opl13;
        case 16:
            goto opl15;
        case 18:
            goto opl16;
        case 20:
            goto opl17;
        case 22:
            goto opl20;
        case 24:
            goto opl21;
        case 26:
            goto opl22;
        case 28:
            goto opl23;
        case 30:
            goto xpr;
        case 32:
            goto opl25;
        case 34:
            goto opl26;
        case 36:
            goto opl27;
        case 38:
            goto opl13;
        case 40:
            goto opl31;
        case 42:
            goto opl32;
        case 44:
            goto xpr;
        case 46:
            goto xpr;
        case 48:
            goto opl35;
        case 50:
            goto opl36;
    }

opl35:
    if (1) {
        sp = 4;
    } else {
opl36:
        sp = 6;
    }
    r4 = expres(r4, &r2, &r3);
    if (r3 == *dotrel) {
        r2 =- *dot;
        if (r2 < 0 && r2 >= -0376) {
            sp = 2;
        }
    }
    *dot =+ sp;
    return r4;

opl13:
opl7:
    r4 = addres(r4, &r0);
op2:
    if (r4 != ',') {
        error("a");
        return r4;
    }
    r4 = readop();
opl15:
    r4 = addres(r4, &r0);
    *dot =+ 2;
    return r4;

opl31:
    r4 = expres(r4, &r2, &r3);
    if (r4 != ',') {
        error("a");
    }
    r4 = readop();
opl6:
opl10:
opl11:
    r4 = expres(r4, &r2, &r3);
    *dot =+ 2;
    return r4;

opl16:
    r4 = expres(r4, &r2, &r3);
    *dot =+ 1;
    if (r4 == ',') {
        r4 = readop();
        goto opl16;
    }
    return r4;

opl17:
    *dot =+ numval;
    r4 = readop();
    return r4;

opl20:
    *dot =+ 1;
    *dot =& ~1;
    return r4;

opl21:
    r4 = expres(r4, &r2, &r3);
    if (r3 == 0) {
        error("U");
    }
    if (r2 == 0) {
        ifflg =+ 1;
    }
opl22:
    return r4;

opl23:
    if (r4 >= 0200) {
        r4->cval =| 040;
        r4 = readop();
        if (r4 == ',') {
            r4 = readop();
            goto opl23;
        }
    }
    return r4;

opl25:
opl26:
opl27:
    /*
    r1 = dotrel;
    r1 =<< 1;
    (r1+(savdot-4))->cval = dot;
    */
    savdot[*dotrel-2] = *dot;
    *dot = savdot[(r0-42)/2];

    r0 =>> 1;
    r0 = r0 - (025-2);
    *dotrel = r0;
    return r4;

opl32:
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
}

addres(r4, r0)
int r4;
int *r0;
{
    int r2, r3;

    if (r4 == '(') {
        goto alp;
    } else if (r4 == '-') {
        goto amin;
    } else if (r4 == '$') {
        goto adoll;
    } else if (r4 == '*') {
        goto astar;
    } else {
        return getx(r4, r0);
    }

alp:
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

amin:
    r4 = readop();
    if (r4 != '(') {
        savop = r4;
        r4 = '-';
        return getx(r4, r0);
    }
    r4 = expres(readop(), &r2, &r3);
    r4 = checkrp(r4);
    checkreg(r2, r3);
    *r0 = 0;
    return r4;

adoll:
    r4 = expres(readop(), &r2, &r3);
    *dot =+ 2;
    *r0 = 0;
    return r4;

astar:
    r4 = readop();
    if (r4 == '*') {
        error("*");
    }
    r4 = addres(r4, r0);
    *dot =+ *r0;
    return r4;
}

getx(r4, r0)
int r4;
int* r0;
{
    int r2, r3;

    r4 = expres(r4, &r2, &r3);
    if (r4 == '(') {
        r4 = expres(readop(), &r2, &r3);
        checkreg(r2, r3);
        r4 = checkrp(r4);
        *dot =+ 2;
        *r0 = 0;
        return r4;
    }

    /* 2: */
    if (r3 == 024) {
        checkreg(r2, r3);
        *r0 = 0;
        return r4;
    }

    /* 1: */
    *dot =+ 2;
    *r0 = 0;
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
