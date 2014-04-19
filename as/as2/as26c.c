/* translated from as26.s */

struct Op { int type, value; };

int passno, line, rlimit, *dotrel, *dot, xsymbol;
int adrbuf[], savdot[], tseeks[], rseeks[], *tseekp, *rseekp;
char argb[], *txtp[], *relp[];

opline(r4)
{
    int r0, r2, r3, *r5, *p, i, tmp1, tmp2, swapf;
    if (r4 == 5) {
        /* file name */
        line = 1;
        memset(argb, 0, 22);
        for (i = 0;; ++i) {
            r4 = getw();
            if (r4 < 0) break;
            if (i < 21) argb[i] = r4;
        }
        return;
    } else if (r4 == '<') {
        goto opl17;
    } else if (0 <= r4 && r4 < 128) {
        expres(r4, &r2, &r3);
        outw(r2, r3);
        return;
    }
    r0 = r4->type;
    tmp1 = r4->value;
    r5 = adrbuf;
    swapf = 0;
    rlimit = -1;
    switch (r0) {
    case  5: goto opl5;
    case  6: goto opl6;
    case  7: goto opl7;
    case  8: /* rts */
        expres(readop(), &r2, &r3);
        checkreg(&r2, &r3);
        outw(r2 | tmp1, r3);
        return;
    case  9: /* sys, emt etc */
        expres(readop(), &r2, &r3);
        if (r2 >= 64 || r3 > 1) error("a");
        outw(r2 | tmp1, r3);
        return;
    case 10: goto opl12;
    case 11: goto opl13;
    case 12: goto opl14;
    case 13: goto opl15;
    case 14: /* .byte */
        do {
            r4 = expres(readop(), &r2, &r3);
            outb(r2, r3);
        } while (r4 == ',');
        return;
    case 15:
        readop();
        goto opl17;
    case 16: /* .even */
        readop();
        if (*dot & 1) {
            if (*dotrel == 4) {
                /* bss mode */
                ++*dot;
            } else {
                outb(0, 0);
            }
        }
        return;
    case 17: /* if */
        expres(readop(), &r2, &r3);
        return;
    case 18: /* .endif */
        return;
    case 19: /* .globl */
        do {
            r4 = readop();
            if (0 <= r4 && r4 < 128) break;
            r4->type =| 32;
            r4 = readop();
        } while (r4 == ',');
        return;
    case 21: /* .text */
    case 22: /* .data */
    case 23: /* .bss  */
        readop();
        ++*dot;
        *dot =& ~1;
        savdot[*dotrel - 2] = *dot;
        if (passno) {
            aflush(txtp);
            aflush(relp);
            r2 = r0 - 21;
            tseekp = &tseeks[r2];
            rseekp = &rseeks[r2];
            oset(txtp, *tseekp);
            oset(relp, *rseekp);
        }
        *dot = savdot[r0 - 21];
        *dotrel = r0 - 19; /* new . relocation */
        return;
    case 24: goto opl30;
    case 25: goto opl31;
    case 26: /* .comm */
        r4 = readop();
        if (r4 < 128) return;
        readop();
        expres(readop(), &r2, &r3);
        if ((r4->type & 31) == 0) {
            r4->type =| 32;
            r4->value = r2;
        }
        return;
    case 29: /* jbr */
    case 30: /* jeq, jne, etc */
        expres(readop(), &r2, &r3);
        if (!passno) {
            r2 = setbr(r2);
            if (r2 && tmp1 != 0000400/*br*/) r2 =+ 2;
            *dot =+ r2; /* if doesn't fit */
            *dot =+ 2;
        } else {
            if (getbr()) goto dobranch;
            if (tmp1 != 0000400/*br*/) {
                /* flip cond, add ".+6" */
                outw(0402 ^ tmp1, 1);
            }
            outw(0000100/*jmp*/ + 037, 1);
            outw(r2, r3);
        }
        return;
    case 20: /* reg */
    case 27: /* est text */
    case 28: /* est data */
    default:
        expres(r4, &r2, &r3);
        outw(r2, r3);
        return;
    }

opl30: /* mpy, dvd etc */
    ++swapf;
    rlimit = 01000;
    goto opl13;

opl14: /* flop freg,fsrc */
    ++swapf;

opl5: /* flop src,freg */
    rlimit = 0400;

opl13: /* double */
    r2 = addres(&r5);
op2a:
    tmp2 = r2;
op2b:
    r2 = addres(&r5);
    if (swapf) {
        r0 = tmp2;
        tmp2 = r2;
        r2 = r0;
    }
    tmp2 = ((tmp2 << 8) + ((tmp2 >> 8) & 255)) >> 2;
    if (rlimit != -1 && tmp2 >= rlimit) error("x");
    outw(r2 | tmp1 | tmp2, 0);
    for (p = adrbuf; p < r5; p =+ 3) {
        outw(p[0], p[1]);
        xsymbol = p[2];
    }
    return;

opl15: /* single operand */
    tmp2 = 0;
    goto op2b;

opl12: /* movf */
    rlimit = 0400;
    r2 = addres(&r5);
    if (r2 >= 4) {
        /* see if source is fregister */
        ++swapf;
    } else {
        tmp1 = 0174000;
    }
    goto op2a;

opl31: /* sob */
    expres(readop(), &r2, &r3);
    checkreg(&r2, &r3);
    r2 = (r2 << 8) + ((r2 >> 8) & 255);
    r2 =>> 2;
    tmp1 =| r2;
    expres(readop(), &r2, &r3);
    if (!passno) {
        outw(r2 | tmp1, 0);
        return;
    }
    r2 =- *dot;
    r2 = -r2;
    if (r2 < -2 || 125 < r2) goto opl6_2;
    r2 =+ 4;
    goto opl6_1;

opl6: /* branch */
    expres(readop(), &r2, &r3);
    if (!passno) {
        outw(r2 | tmp1, 0);
        return;
    }
dobranch:
    r2 =- *dot;
    if (r2 < -254 || 256 < r2) goto opl6_2;
opl6_1:
    if (r2 & 1) goto opl6_2;
    if (r3 != *dotrel) goto opl6_2; /* same relocation as . */
    outw((((r2 >> 1) - 1) & ~0177400) | tmp1, 0);
    return;
opl6_2:
    error("b");
    outw(tmp1, 0);
    return;

opl7: /* jsr */
    expres(readop(), &r2, &r3);
    checkreg(&r2, &r3);
    goto op2a;

opl17: /* < (.ascii) */
    for (;;) {
        if ((r4 = getw()) < 0) break;
        outb(r4 & 255, 1);
    }
    getw();
    return;
}

int savop;

addres(r5)
int **r5;
{
    return addres1(r5, 0);
}

addres1(r5, astar)
int **r5;
{
    int r1, r2, r3, r4;
    switch (r4 = readop()) {
    case '(':
        r4 = expres(readop(), &r2, &r3);
        r4 = checkrp(r4);
        checkreg(&r2, &r3);
        if (r4 == '+') {
            r4 = readop();
            return r2 | 020;
        } else if (astar) {
            *((*r5)++) = 0;
            *((*r5)++) = 0;
            *((*r5)++) = xsymbol;
            return r2 | 070;
        }
        return r2 | 010;
    case '-':
        r4 = readop();
        if (r4 != '(') {
            savop = r4;
            r4 = '-';
            break;
        }
        r4 = expres(readop(), &r2, &r3);
        r4 = checkrp(r4);
        checkreg(&r2, &r3);
        return r2 | 040;
    case '$':
        r4 = expres(readop(), &r2, &r3);
        *((*r5)++) = r2;
        *((*r5)++) = r3;
        *((*r5)++) = xsymbol;
        return 027;
    case '*':
        if (astar) error("*");
        return addres1(r5, 1) | 010;
    }
    r4 = expres(r4, &r2, &r3);
    if (r4 == '(') {
        *((*r5)++) = r2;
        *((*r5)++) = r3;
        *((*r5)++) = xsymbol;
        r4 = expres(readop(), &r2, &r3);
        checkreg(&r2, &r3);
        r4 = checkrp(r4);
        return r2 | 060;
    } else if (r3 == 20) {
        checkreg(&r2, &r3);
        return r2;
    }
    r3 =| 0100000;
    r2 =- *dot + 4;
    if (*r5 != adrbuf) r2 =- 2;
    *((*r5)++) = r2; /* index */
    *((*r5)++) = r3; /* index reloc. */
    *((*r5)++) = xsymbol; /* index global */
    return 067; /* address mode */
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
    r0 =- *dot;
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
