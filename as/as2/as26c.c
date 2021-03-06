/* translated from as26.s */

struct Op { char type, num; int value; };

extern int passno, line, *dotrel, *dot, abufi;
extern int adrbuf[], savdot[], tseeks[], rseeks[];
extern char *txtp[], *relp[], *xsymbol;

opline(op)
{
    struct Op x;
    int w, optype, opcode, opr, len;
    if (op == '<') {
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
        opr = addres();
        op2b(opcode, opr, addres(), 4);
        break;
    case 6: /* branch */
        expres(&x, readop());
        if (passno < 2) {
            *dot =+ 2;
        } else {
            x.value =- *dot + 2; /* pc relative */
            dobranch(&x, opcode, -256, 254);
        }
        break;
    case 7: /* jsr */
        expres(&x, readop());
        checkreg(&x);
        checkop(','); /* skip , */
        op2b(opcode, x.value, addres(), -1);
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
        opr = addres();
        if (opr >= 4) {
            /* see if source is fregister */
            op2b(opcode, addres(), opr, 4);
        } else {
            op2b(0174000, opr, addres(), -1);
        }
        break;
    case 11: /* double */
        opr = addres();
        op2b(opcode, opr, addres(), -1);
        break;
    case 12: /* flop freg,fsrc */
        opr = addres();
        op2b(opcode, addres(), opr, 4);
        break;
    case 13: /* single operand */
        op2b(opcode, 0, addres(), -1);
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
        savdot[*dotrel - 2] = (*dot + 1) & ~1;
        if (passno == 2) {
            aflush(txtp);
            aflush(relp);
            oset(txtp, tseeks[optype - 21]);
            oset(relp, rseeks[optype - 21]);
        }
        *dot = savdot[optype - 21];
        *dotrel = optype - 19; /* new . relocation */
        break;
    case 24: /* mpy, dvd etc */
        opr = addres();
        op2b(opcode, addres(), opr, 010);
        break;
    case 25: /* sob */
        expres(&x, readop());
        checkreg(&x);
        opcode =| x.value << 6;
        checkop(','); /* skip , */
        expres(&x, readop());
        if (passno < 2) {
            *dot =+ 2;
        } else {
            x.value = (*dot + 2) - x.value; /* back only */
            dobranch(&x, opcode, 0, 126);
        }
        break;
    case 26: /* .comm */
        op = readop();
        if (!issym(op)) break; /* checked by as1 */
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
        if (passno < 2) {
            len = op->type == 29 ? 4 : 6;
            x.value =- *dot + 2; /* pc relative */
            if (setbr(x.value, len)) {
                *dot =+ 2;
            } else {
                /* if doesn't fit */
                *dot =+ len;
            }
        } else {
            if (getbr()) {
                x.value =- *dot + 2; /* pc relative */
                dobranch(&x, opcode, -256, 254);
            } else {
                if (optype != 29/*jbr*/) {
                    /* flip cond, add ".+6" */
                    outw(1, opcode ^ 0402);
                }
                outw(1, 0000137); /* jmp *$A */
                outw(x.type, x.value); /* absolute */
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

op2b(opcode, opr1, opr2, rlimit)
{
    int i;
    if (rlimit != -1 && opr1 >= rlimit) error("x");
    outw(0, opcode | (opr1 << 6) | opr2);
    for (i = 0; i < abufi; i =+ 3) {
        xsymbol = adrbuf[i + 2];
        outw(adrbuf[i + 1], adrbuf[i]);
    }
}

dobranch(this, opcode, min, max)
struct Op *this;
{
    if (this->value < min || max < this->value
            || this->value & 1 /* (must) even */
            || this->type != *dotrel /* (must) same relocation as . */) {
        error("b");
        outw(0, opcode);
    } else {
        outw(0, opcode | ((this->value >> 1) & 255));
    }
}

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
    if (this->value > 7 || (1 < this->type && this->type < 5)) {
        error("a");
        this->type = this->value = 0;
    }
}

extern int savop;

/* checkrp()を汎用化（独自関数） */
checkop(ch)
{
    int op;
    if ((op = readop()) == ch) return 1;
    savop = op;
    return 0;
}

extern int brtabi, brlen, brdelt;
extern char brtab[];

/* 戻り値の意味をオリジナルと逆転 */
setbr(rel, len)
{
    int i;
    i = brtabi;
    if (i >= brlen) return 0; /* not fit */
    ++brtabi;
    /* 前方参照の誤差を補正 */
    if (rel > -2) rel =- brdelt;
    if (rel < -254 || 256 < rel) return 0; /* not fit */
    /* 前方参照の短縮による誤差を計上 */
    if (rel > -2) brdelt =+ len - 2;
    /* set bitmap */
    brtab[i >> 3] =| 1 << (i & 7);
    return 1; /* fit */
}

/* 戻り値の意味をオリジナルと逆転 */
getbr()
{
    int i;
    i = brtabi;
    if (i >= brlen) return 0; /* not fit */
    ++brtabi;
    /* get bitmap */
    return (brtab[i >> 3] >> (i & 7)) & 1;
}

/* トークンがシンボルかどうかを判定（独自関数） */
issym(op)
{
    return op < 0 || 127 < op;
}
