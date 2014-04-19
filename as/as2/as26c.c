/* translated from as26.s */

struct Op { int type, value; };

int passno, line, *dotrel, *dot, xsymbol;
int adrbuf[], savdot[], tseeks[], rseeks[], *tseekp, *rseekp;
char argb[], *txtp[], *relp[];

opline(r4)
{
    struct Op x;
    int r0, r2, *r5, *p, i, tmp1, tmp2;
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
        opl17();
        return;
    } else if (0 <= r4 && r4 < 128) {
        expres(&x, r4);
        outw(x.value, x.type);
        return;
    }
    r0 = r4->type;
    tmp1 = r4->value;
    r5 = adrbuf;
    switch (r0) {
    case 5: /* flop src,freg */
        tmp2 = addres(&r5);
        op2b(r5, tmp1, tmp2, 0, 0400);
        break;
    case 6: /* branch */
        expres(&x, readop());
        if (!passno) {
            outw(x.value | tmp1, 0);
        } else {
            dobranch(&x, tmp1, 0);
        }
        break;
    case 7: /* jsr */
        expres(&x, readop());
        checkreg(&x);
        op2b(r5, tmp1, x.value, 0, -1);
        break;
    case 8: /* rts */
        expres(&x, readop());
        checkreg(&x);
        outw(x.value | tmp1, x.type);
        break;
    case 9: /* sys, emt etc */
        expres(&x, readop());
        if (x.value >= 64 || x.type > 1) error("a");
        outw(x.value | tmp1, x.type);
        break;
    case 10: /* movf */
        tmp2 = addres(&r5);
        if (tmp2 >= 4) {
            /* see if source is fregister */
            op2b(r5, tmp1, tmp2, 1, 0400);
        } else {
            op2b(r5, 0174000, tmp2, 0, 0400);
        }
        break;
    case 11: /* double */
        tmp2 = addres(&r5);
        op2b(r5, tmp1, tmp2, 0, -1);
        break;
    case 12: /* flop freg,fsrc */
        tmp2 = addres(&r5);
        op2b(r5, tmp1, tmp2, 1, 0400);
        break;
    case 13: /* single operand */
        op2b(r5, tmp1, 0, 0, -1);
        break;
    case 14: /* .byte */
        do {
            r4 = expres(&x, readop());
            outb(x.value, x.type);
        } while (r4 == ',');
        break;
    case 15:
        readop();
        opl17();
        break;
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
        break;
    case 17: /* if */
        expres(&x, readop());
        break;
    case 18: /* .endif */
        break;
    case 19: /* .globl */
        do {
            r4 = readop();
            if (0 <= r4 && r4 < 128) break;
            r4->type =| 32;
            r4 = readop();
        } while (r4 == ',');
        break;
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
    case 24: /* mpy, dvd etc */
        tmp2 = addres(&r5);
        op2b(r5, tmp1, tmp2, 1, 01000);
        break;
    case 25: /* sob */
        expres(&x, readop());
        checkreg(&x);
        tmp1 =| ((x.value << 8) + ((x.value >> 8) & 255)) >> 2;
        expres(&x, readop());
        if (!passno) {
            outw(x.value | tmp1, 0);
            return;
        }
        x.value =- *dot;
        x.value = -x.value;
        if (x.value < -2 || 125 < x.value) {
            error("b");
            outw(tmp1, 0);
        } else {
            x.value =+ 4;
            dobranch(&x, tmp1, 1);
        }
        break;
    case 26: /* .comm */
        r4 = readop();
        if (r4 < 128) return;
        readop();
        expres(&x, readop());
        if ((r4->type & 31) == 0) {
            r4->type =| 32;
            r4->value = x.value;
        }
        break;
    case 29: /* jbr */
    case 30: /* jeq, jne, etc */
        expres(&x, readop());
        if (!passno) {
            r2 = setbr(x.value);
            if (r2 && tmp1 != 0000400/*br*/) r2 =+ 2;
            *dot =+ r2; /* if doesn't fit */
            *dot =+ 2;
        } else {
            if (getbr()) {
                dobranch(&x, tmp1, 0);
            } else {
                if (tmp1 != 0000400/*br*/) {
                    /* flip cond, add ".+6" */
                    outw(0402 ^ tmp1, 1);
                }
                outw(0000100/*jmp*/ + 037, 1);
                outw(x.value, x.type);
            }
        }
        break;
    case 20: /* reg */
    case 27: /* est text */
    case 28: /* est data */
    default:
        expres(&x, r4);
        outw(x.value, x.type);
        break;
    }
}

op2b(r5, tmp1, tmp2, swapf, rlimit)
int *r5;
{
    int r0, r2, *p;
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
}

dobranch(this, opcode, sob)
struct Op *this;
{
    if (!sob) this->value =- *dot;
    if ((!sob && this->value < -254 || 256 < this->value)
        || this->value & 1
        || this->type != *dotrel /* same relocation as . */) {
        error("b");
        outw(opcode, 0);
    } else {
        outw((((this->value >> 1) - 1) & ~0177400) | opcode, 0);
    }
}

/* < (.ascii) */
opl17()
{
    int w;
    for (;;) {
        if ((w = getw()) < 0) break;
        outb(w & 255, 1);
    }
    getw();
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
    struct Op x;
    int r1, r4;
    switch (r4 = readop()) {
    case '(':
        r4 = expres(&x, readop());
        r4 = checkrp(r4);
        checkreg(&x);
        if (r4 == '+') {
            r4 = readop();
            return x.value | 020;
        } else if (astar) {
            *((*r5)++) = 0;
            *((*r5)++) = 0;
            *((*r5)++) = xsymbol;
            return x.value | 070;
        }
        return x.value | 010;
    case '-':
        r4 = readop();
        if (r4 != '(') {
            savop = r4;
            r4 = '-';
            break;
        }
        r4 = expres(&x, readop());
        r4 = checkrp(r4);
        checkreg(&x);
        return x.value | 040;
    case '$':
        r4 = expres(&x, readop());
        *((*r5)++) = x.value;
        *((*r5)++) = x.type;
        *((*r5)++) = xsymbol;
        return 027;
    case '*':
        if (astar) error("*");
        return addres1(r5, 1) | 010;
    }
    r4 = expres(&x, r4);
    if (r4 == '(') {
        *((*r5)++) = x.value;
        *((*r5)++) = x.type;
        *((*r5)++) = xsymbol;
        r4 = expres(&x, readop());
        checkreg(&x);
        r4 = checkrp(r4);
        return x.value | 060;
    } else if (x.type == 20) {
        checkreg(&x);
        return x.value;
    }
    x.type =| 0100000;
    x.value =- *dot + 4;
    if (*r5 != adrbuf) x.value =- 2;
    *((*r5)++) = x.value; /* index */
    *((*r5)++) = x.type;  /* index reloc. */
    *((*r5)++) = xsymbol; /* index global */
    return 067; /* address mode */
}

checkreg(this)
struct Op *this;
{
    if (this->value > 7 || (this->value > 1 && this->type < 5)) {
        error("a");
        this->type = this->value = 0;
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
