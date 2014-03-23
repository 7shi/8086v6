/* translated from as16.s */

int dot;
int dotrel;
int savdot;
int savop;
int ifflg;
int numval;

struct { char cval; };

opline(r2, r3, r4)
int r2;
int r3;
int r4;
{
    int r0, r1, sp;

    r0 = r4;
    if (0 <= r0 && r0 <= 0200) {
        if (r0 == '<') {
            goto opl17;
        }
/* xpr: */
xpr:
        r4 = expres(r4, r2, r3);
        dot =+ 2;
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
        case 0:     /* r0 == 5 */
            goto opl13;
        case 2:     /* r0 == 6 */
            goto opl6;
        case 4:     /* r0 == 7 */
            goto opl7;
        case 6:     /* r0 == 8 */
            goto opl10;
        case 8:     /* r0 == 9 */
            goto opl11;
        case 10:     /* r0 == 10 */
            goto opl13;
        case 12:     /* r0 == 11 */
            goto opl13;
        case 14:     /* r0 == 12 */
            goto opl13;
        case 16:     /* r0 == 13 */
            goto opl15;
        case 18:     /* r0 == 14 */
            goto opl16;
        case 20:     /* r0 == 15 */
            goto opl17;
        case 22:     /* r0 == 16 */
            goto opl20;
        case 24:     /* r0 == 17 */
            goto opl21;
        case 26:     /* r0 == 18 */
            goto opl22;
        case 28:     /* r0 == 19 */
            goto opl23;
        case 30:     /* r0 == 20 */
            goto xpr;
        case 32:     /* r0 == 21 */
            goto opl25;
        case 34:     /* r0 == 22 */
            goto opl26;
        case 36:     /* r0 == 23 */
            goto opl27;
        case 38:     /* r0 == 24 */
            goto opl13;
        case 40:     /* r0 == 25 */
            goto opl31;
        case 42:     /* r0 == 26 */
            goto opl32;
        case 44:     /* r0 == 27 */
            goto xpr;
        case 46:     /* r0 == 28 */
            goto xpr;
        case 48:     /* r0 == 29 */
            goto opl35;
        case 50:     /* r0 == 30 */
            goto opl36;
    }

opl35:
    if (1) {
        sp = 4;
    } else {
opl36:
        sp = 6;
    }
    r4 = expres(r4, r2, r3);
    if (r3 == dotrel) {
        r2 =- dot;
        if (r2 < 0 && r2 >= -0376) {
            sp = 2;
        }
    }
    dot = sp;
    return r4;

opl13:
opl7:
    addres(r2, r3, r4);
op2:
    if (r4 != ',') {
        errora();
        return r4;
    }
    r4 = readop();
opl15:
    addres(r2, r3, r4);
    dot =+ 2;
    return r4;

opl31:
    r4 = expres(r4, r2, r3);
    if (r4 != ',') {
        errora();
    } else {
        r4 = readop();
    }
opl6:
opl10:
opl11:
    r4 = expres(r4, r2, r3);
    dot =+ 2;
    return r4;

opl16:
    r4 = expres(r4, r2, r3);
    dot =+ 1;
    if (r4 == ',') {
        r4 = readop();
        goto opl16;
    }
    return r4;

opl17:
    dot =+ numval;
    r4 = readop();
    return r4;

opl20:
    dot =+ 1;
    dot =& ~1;
    return r4;

opl21:
    r4 = expres(r4, r2, r3);
    if (r3 == 0) {
        error('U');
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
    r1 = dotrel;
    r1 =<< 1;
    /* mov dot,savdot-4(r1) */

    r0 =>> 1;
    r0 = r0 - 025 - 2;
    dotrel = r0;
    return r4;

opl32:
    if (r4 >= 0200) {
        r4->cval =| 040;
        r4 = readop();
        if (r4 != ',') {
            r4 = expres(readop(), r2, r3);
            return r4;
        }
    }
    error('x');
    return r4;
}

addres(r2, r3, r4)
int r2;
int r3;
int r4;
{
    int r0;

    if (r4 == '(') {
        goto alp;
    } else if (r4 == '-') {
        goto amin;
    } else if (r4 == '$') {
        goto adoll;
    } else if (r4 == '*') {
        goto astar;
    }

    return getx(r2, r3, r4);

alp:
    r4 = expres(readop(), r2, r3);
    checkreg(r2,r3);
    checkrp(r4);
    if (r4 == '+') {
        r4 = readop();
        return ;
    }
    r0 = 2;
    return ;

amin:
    r4 = readop();
    if (r4 != '(') {
        savop = r4;
        r4 = '-';
        return getx(r2, r3, r4);
    }
    r4 = expres(readop(), r2, r3);
    checkrp(r4);
    checkreg(r2, r3);
    return ;

adoll:
    r4 = expres(readop(), r2, r3);
    dot =+ 2;
    return ;

astar:
    r4 = readop();
    if (r4 == '*') {
        error('*');
    }
    addres(r2, r3, r4);
    dot =+ r0;
    return; 
}

getx(r2, r3, r4)
int r2;
int r3;
int r4;
{
    r4 = expres(r4, r2, r3);
    if (r4 == '(') {
        r4 = expres(readop(), r2, r3);
        checkreg(r2, r3);
        checkrp(r4);
        dot =+ 2;
        return;
    }

    /* 2: */
    if (r3 == 024) {
        checkreg(r2, r3);
        return ;
    }

    /* 1: */
    dot =+ 2;
    return ;
}


checkreg(r2, r3)
int r2;
int r3;
{
    if (r2 < 7) {
        if (r3 == 1 || r3 > 4) {
            return ;
        }
    }

    errora();
    return ;
}

checkrp(r4)
int r4;
{
    if (r4 == ')') {
        r4 = readop();
    } else {
        error(')');
    }
    return ;
}

errora()
{
    error('a');
    return ;
}

errore()
{
    error('e');
    return ;
}
