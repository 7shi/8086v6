/* translated from as26.s */

struct Op { char type, num; int value; };

int passno, line, *dotrel, *dot, abufi;
int adrbuf[], savdot[], tseeks[], rseeks[], *tseekp, *rseekp;
char argb[], *txtp[], *relp[], *xsymbol;

opline(op)
{
    struct Op x;
    int w, br, i, optype, opcode, ad;
    if (op == 5) {
        /* file name */
        line = 1;
        memset(argb, 0, 22);
        for (i = 0;; ++i) {
            w = getw();
            if (w < 0) break;
            if (i < 21) argb[i] = w;
        }
        return;
    } else if (op == '<') {
        while ((w = getw()) != -1) {
            outb(1, w & 255);
        }
        return;
    } else if (!issym(op)) {
        expres(&x, op);
        outw(x.type, x.value);
        return;
    }
    optype = op->type;
    opcode = op->value;
    abufi = 0;
    switch (optype) {
    case 5: /* flop src,freg */
        ad = addres();
        op2b(opcode, ad, 0, 0400);
        break;
    case 6: /* branch */
        expres(&x, readop());
        if (!passno) {
            outw(0, opcode | x.value);
        } else {
            dobranch(&x, opcode, 0);
        }
        break;
    case 7: /* jsr */
        expres(&x, readop());
        checkreg(&x);
        checkop(','); /* skip , */
        op2b(opcode, x.value, 0, -1);
        break;
    case 8: /* rts */
        expres(&x, readop());
        checkreg(&x);
        outw(x.type, opcode | x.value);
        break;
    case 9: /* sys, emt etc */
        expres(&x, readop());
        if (x.value >= 64 || x.type > 1) error("a");
        outw(x.type, opcode | x.value);
        break;
    case 10: /* movf */
        ad = addres();
        if (ad >= 4) {
            /* see if source is fregister */
            op2b(opcode, ad, 1, 0400);
        } else {
            op2b(0174000, ad, 0, 0400);
        }
        break;
    case 11: /* double */
        ad = addres();
        op2b(opcode, ad, 0, -1);
        break;
    case 12: /* flop freg,fsrc */
        ad = addres();
        op2b(opcode, ad, 1, 0400);
        break;
    case 13: /* single operand */
        op2b(opcode, 0, 0, -1);
        break;
    case 14: /* .byte */
        do {
            expres(&x, readop());
            outb(x.type, x.value);
        } while (checkop(','));
        break;
    case 15: /* < (.ascii) */
        /* not used */
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
            op = readop();
            if (!issym(op)) break;
            op->type =| 32;
        } while (checkop(','));
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
            tseekp = &tseeks[optype - 21];
            rseekp = &rseeks[optype - 21];
            oset(txtp, *tseekp);
            oset(relp, *rseekp);
        }
        *dot = savdot[optype - 21];
        *dotrel = optype - 19; /* new . relocation */
        return;
    case 24: /* mpy, dvd etc */
        ad = addres();
        op2b(opcode, ad, 1, 01000);
        break;
    case 25: /* sob */
        expres(&x, readop());
        checkreg(&x);
        opcode =| x.value << 6;
        checkop(','); /* skip , */
        expres(&x, readop());
        if (!passno) {
            outw(0, opcode | x.value);
            return;
        }
        x.value =- *dot;
        x.value = -x.value;
        if (x.value < -2 || 125 < x.value) {
            error("b");
            outw(0, opcode);
        } else {
            x.value =+ 4;
            dobranch(&x, opcode, 1);
        }
        break;
    case 26: /* .comm */
        op = readop();
        if (!issym(op)) return;
        checkop(','); /* skip , */
        expres(&x, readop());
        if ((op->type & 31) == 0) {
            op->type =| 32;
            op->value = x.value;
        }
        break;
    case 29: /* jbr */
    case 30: /* jeq, jne, etc */
        expres(&x, readop());
        if (!passno) {
            br = setbr(x.value);
            if (br && optype != 29/*jbr*/) br =+ 2;
            *dot =+ br; /* if doesn't fit */
            *dot =+ 2;
        } else {
            if (!getbr()) {
                dobranch(&x, opcode, 0);
            } else {
                if (optype != 29/*jbr*/) {
                    /* flip cond, add ".+6" */
                    outw(1, opcode ^ 0402);
                }
                outw(1, 0000137); /* jmp *$A */
                outw(x.type, x.value);
            }
        }
        break;
    case 20: /* reg */
    case 27: /* est text */
    case 28: /* est data */
    default:
        expres(&x, op);
        outw(x.type, x.value);
        break;
    }
}

op2b(opcode, ad1, swapf, rlimit)
{
    int ad2, i, tmp;
    ad2 = addres();
    if (swapf) {
        tmp = ad1;
        ad1 = ad2;
        ad2 = tmp;
    }
    ad1 =<< 6;
    if (rlimit != -1 && ad1 >= rlimit) error("x");
    outw(0, opcode | ad1 | ad2);
    for (i = 0; i < abufi; i =+ 3) {
        xsymbol = adrbuf[i + 2];
        outw(adrbuf[i + 1], adrbuf[i]);
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
        outw(0, opcode);
    } else {
        outw(0, opcode | (((this->value - 2) >> 1) & 255));
    }
}

int savop;

addres()
{
    int ret;
    ret = addres1(0);
    checkop(','); /* skip , */
    return ret;
}

addres1(astar)
{
    struct Op x;
    int op;
    switch (op = readop()) {
    case '(':
        expres(&x, readop());
        if (!checkop(')')) error(")");
        checkreg(&x);
        if (checkop('+')) {
            return x.value | 020;
        }
        if (astar) {
            adrbuf[abufi++] = 0;
            adrbuf[abufi++] = 0;
            adrbuf[abufi++] = xsymbol;
            return x.value | 070;
        }
        return x.value | 010;
    case '-':
        if (!checkop('(')) {
            op = '-';
            break;
        }
        expres(&x, readop());
        if (!checkop(')')) error(")");
        checkreg(&x);
        return x.value | 040;
    case '$':
        expres(&x, readop());
        adrbuf[abufi++] = x.value;
        adrbuf[abufi++] = x.type;
        adrbuf[abufi++] = xsymbol;
        return 027;
    case '*':
        if (astar) error("*");
        return addres1(1) | 010;
    }
    expres(&x, op);
    if (checkop('(')) {
        adrbuf[abufi++] = x.value;
        adrbuf[abufi++] = x.type;
        adrbuf[abufi++] = xsymbol;
        expres(&x, readop());
        if (!checkop(')')) error(")");
        checkreg(&x);
        return x.value | 060;
    } else if (x.type == 20) {
        checkreg(&x);
        return x.value;
    }
    x.value =- *dot + 4;
    if (abufi) x.value =- 2;
    adrbuf[abufi++] = x.value; /* index */
    adrbuf[abufi++] = -x.type; /* index reloc. */
    adrbuf[abufi++] = xsymbol; /* index global */
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

/* checkrp()を汎用化（独自関数） */
checkop(ch)
{
    int op;
    if ((op = readop()) == ch) return 1;
    savop = op;
    return 0;
}

int brtabi, brlen, brdelt;
char brtab[];

setbr(ad)
{
    int i, rel;
    i = brtabi;
    if (i >= brlen) return 2;
    ++brtabi;
    rel = ad - *dot;
    if (rel > 0) rel =- brdelt;
    if (-254 <= rel && rel <= 256) return 0;
    brtab[i >> 3] =| 1 << (i & 7);
    return 2;
}

getbr()
{
    int i;
    i = brtabi;
    if (i >= brlen) return 1;
    ++brtabi;
    /* 0-bit into c-bit */
    return (brtab[i >> 3] >> (i & 7)) & 1;
}

/* トークンがシンボルかどうかを判定（独自関数） */
issym(op)
{
    return op < 0 || 127 < op;
}
