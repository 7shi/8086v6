/* translated from as26.s */

struct Op { int type, value; };
struct { char cval; };

int passno, line, swapf, rlimit, dotrel, dot, xsymbol, txtseek, trelseek;
int *rseekp, *tseekp;
int adrbuf[], savdot[];
char argb[], *txtp[], *relp[];

opline_(r4)
{
    int r0, r1, *r1p, r2, r3, *r5, tmp, tmp2;
    r0 = r4;
    if (r0 < 0 || 127 < r0) goto opline2;
    if (r4 == 5) goto opeof;
    if (r4 != '<') goto xpr;
    goto opl17;
xxpr:
xpr:
    r4 = expres(r4, &r2, &r3);
    outw(r2, r3);
    return r4;
opline2:
    r0 = r4->cval;
    if (r0 == 20) goto xpr; /* reg */
    if (r0 == 27) goto xpr; /* est text */
    if (r0 == 28) goto xpr; /* est data */
    if (r0 < 5 || 30 < r0) goto xpr;
    tmp = r4->value;
    r4 = readop();
    r5 = adrbuf;
    swapf = 0;
    rlimit = -1;
    switch (r0) {
    case  5: goto opl5;
    case  6: goto opl6;
    case  7: goto opl7;
    case  8: goto opl10;
    case  9: goto opl11;
    case 10: goto opl12;
    case 11: goto opl13;
    case 12: goto opl14;
    case 13: goto opl15;
    case 14: goto opl16;
    case 15: goto opl17;
    case 16: goto opl20;
    case 17: goto opl21;
    case 18: goto opl22;
    case 19: goto opl23;
    case 20: goto xxpr;
    case 21: goto opl25;
    case 22: goto opl26;
    case 23: goto opl27;
    case 24: goto opl30;
    case 25: goto opl31;
    case 26: goto opl32;
    case 27: goto xxpr;
    case 28: goto xxpr;
    case 29: goto opl35;
    case 30: goto opl36;
    }

opeof:
    line = 1;
    tmp = 16;
    r1 = argb;
    for (;;) {
        r4 = getw();
        if (r4 < 0) break;
        (r1++)->cval = r4;
        --tmp;
        if (tmp <= 0) --r1;
    }
    (r1++)->cval = '\n';
    (r1++)->cval = 0;
    return r4;

opl30: /* mpy, dvd etc */
    ++swapf;
    rlimit = 01000;
    goto opl13;

opl14: /* flop freg,fsrc */
    ++swapf;

opl5: /* flop src,freg */
    rlimit = 0400;

opl13: /* double */
    r4 = addres(r4, &r5, &r2);
op2a:
    tmp2 = r2;
    r4 = readop();
op2b:
    r4 = addres(r4, &r5, &r2);
    if (swapf) {
        r0 = tmp2;
        tmp2 = r2;
        r2 = r0;
    }
    tmp2 = (tmp2 << 8) + ((tmp2 >> 8) & 255);
    tmp2 =>> 2;
    if (tmp2 >= rlimit) error("x");
    r2 =| tmp2;
    r2 =| tmp;
    r3 = 0;
    outw(r2, r3);
    r1p = adrbuf;
    while (r1p < r5) {
        r2 = *(r1p++);
        r3 = *(r1p++);
        xsymbol = *(r1p++);
        outw(r2, r3);
    }
    return r4;

opl15: /* single operand */
    tmp2 = 0;
    goto op2b;

opl12: /* movf */
    rlimit = 0400;
    r4 = addres(r4, &r5, &r2);
    if (r2 >= 4) {
        /* see if source is fregister */
        ++swapf;
    } else {
        tmp = 0174000;
    }
    goto op2a;

opl35: /* jbr */
opl36: /* jeq, jne, etc */
    r4 = expres(r4, &r2, &r3);
    if (!passno) {
        r0 = r2;
        r2 = setbr(r0);
        if (r2 && tmp != 0000400/*br*/) r2 =+ 2;
        dot =+ r2; /* if doesn't fit */
        dot =+ 2;
    } else {
        if (getbr()) goto dobranch;
        r0 = tmp;
        if (r0 != 0000400/*br*/) {
            /* flip cond, add ".+6" */
            outw(0402 ^ r0, 1);
        }
        outw(0000100/*jmp*/ + 037, 1);
        outw(r2, r3);
    }
    return r4;

opl31: /* sob */
    r4 = expres(r4, &r2, &r3);
    checkreg(&r2, &r3);
    r2 = (r2 << 8) + ((r2 >> 8) & 255);
    r2 =>> 2;
    tmp =| r2;
    r4 = readop();
    r4 = expres(r4, &r2, &r3);
    if (!passno) goto opl6_3;
    r2 =- dot;
    r2 = -r2;
    r0 = r2;
    if (r0 < -2 || 125 < r0) goto opl6_2;
    r2 =+ 4;
    goto opl6_1;

opl6: /* branch */
    r4 = expres(r4, &r2, &r3);
    if (!passno) goto opl6_3;
dobranch:
    r2 =- dot;
    r0 = r2;
    if (r0 < -254 || 256 < r0) goto opl6_2;
opl6_1:
    if (r2 & 1) goto opl6_2;
    if (r3 != &dotrel) goto opl6_2; /* same relocation as . */
    r2 =>> 1;
    --r2;
    r2 =& ~0177400;
opl6_3:
    r2 =| tmp;
    r3 = 0;
    outw(r2, r3);
    return r4;
opl6_2:
    error("b");
    r2 = 0;
    goto opl6_3;

opl7: /* jsr */
    r4 = expres(r4, &r2, &r3);
    checkreg(&r2, &r3);
    goto op2a;

opl10: /* rts */
    r4 = expres(r4, &r2, &r3);
    checkreg(&r2, &r3);
    goto opl11_1;

opl11: /* sys, emt etc */
    r4 = expres(r4, &r2, &r3);
    if (r2 >= 64 || r3 > 1) error("a");
opl11_1:
    r2 =| tmp;
    outw(r2, r3);
    return r4;

opl16: /* .byte */
    r4 = expres(r4, &r2, &r3);
    outb(r2, r3);
    if (r4 == ',') {
        r4 = readop();
        goto opl16;
    }
    return r4;

opl17: /* < (.ascii) */
    r4 = getw();
    r3 = 1;
    r2 = r4;
    if (r2 >= 0) {
        r2 =& 255;
        outb(r2, r3);
        goto opl17;
    }
    r4 = getw();
    return r4;

opl20: /* .even */
    if (dot & 1 == 0) return r4;
    if (dotrel == 4) {
        /* bss mode */
        ++dot;
    } else {
        r2 = r3 = 0;
        outb(r2, r3);
    }
    return r4;

opl21: /* if */
    r4 = expres(r4, &r2, &r3);
opl22:
oplret:
    return r4;

opl23: /* .globl */
    if (r4 >= 128) {
        r4->cval =| 32;
        r4 = readop();
        if (r4 == ',') {
            r4 = readop();
            goto opl23;
        }
    }
    return r4;

opl25: /* .text */
opl26: /* .data */
opl27: /* .bss */
    ++dot;
    dot =& ~1;
    tmp2 = r0;
    r1 = dotrel;
    r1 =<< 1;
    savdot[r1 - 4] = dot;
    if (passno) {
        flush(txtp);
        flush(relp);
        r2 = tmp2 - 25;
        tseekp = &txtseek + r2;
        rseekp = &trelseek + r2;
        oset(*tseekp, txtp);
        oset(*rseekp, relp);
    }
    r0 = tmp2;
    dot = savdot[r0 - 21];
    r0 =>> 1;
    r0 =- 19;
    dotrel = r0; /* new . relocation */
    return r4;

opl32:
    if (r4 < 128) return r4;
    tmp = r4;
    r4 = readop();
    r4 = readop();
    r4 = expres(r4, &r2, &r3);
    r0 = tmp;
    if ((r0->type & 31) == 0) {
        r0->type =| 32;
        r0->value = r2;
    }
    return r4;
}

int savop;

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
