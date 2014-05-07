/* translated from as26.s */

struct Op { char type, num; int value; };

int passno, line, *dotrel, *dot, abufi;
int savop, numval, ifflg;
int adrbuf[], savdot[], tseeks[], rseeks[];
char argb[], *txtp[], *relp[], *xsymbol;

opline(op)
{
    struct Op x;
    int w, i, optype, opcode, opr, len;
    if (passno && op == 5) {
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
        if (passno == 0) {
            *dot =+ numval;
        } else {
            while ((w = getw()) != -1) {
                outb(1, w & 255);
            }
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
        opr = _addres();
        if (!checkop(',')) return error("a");
        op2b(opcode, opr, _addres(), 4);
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
        _checkreg(&x);
        if (!checkop(',')) return error("a");
        op2b(opcode, x.value, _addres(), -1);
        break;
    case 8: /* rts */
        expres(&x, readop());
        _checkreg(&x);
        outw(x.type, opcode | x.value);
        break;
    case 9: /* sys, emt etc */
        expres(&x, readop());
        if (x.value >= 64 || x.type > 1) return error("a");
        outw(x.type, opcode | x.value);
        break;
    case 10: /* movf */
        opr = _addres();
        if (!checkop(',')) return error("a");
        if (opr >= 4) {
            /* see if source is fregister */
            op2b(opcode, _addres(), opr, 4);
        } else {
            op2b(0174000, opr, _addres(), -1);
        }
        break;
    case 11: /* double */
        opr = _addres();
        if (!checkop(',')) return error("a");
        op2b(opcode, opr, _addres(), -1);
        break;
    case 12: /* flop freg,fsrc */
        opr = _addres();
        if (!checkop(',')) return error("a");
        op2b(opcode, _addres(), opr, 4);
        break;
    case 13: /* single operand */
        op2b(opcode, 0, _addres(), -1);
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
    case 17: /* .if */
        expres(&x, readop());
        if (passno == 0) {
            if (x.type  == 0) error("U");
            if (x.value == 0) ++ifflg;
        }
        break;
    case 18: /* .endif */
        break;
    case 19: /* .globl */
        do {
            if (!issym(op = readop())) {
                savop = op;
                break;
            }
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
        opr = _addres();
        if (!checkop(',')) return error("a");
        op2b(opcode, _addres(), opr, 010);
        break;
    case 25: /* sob */
        expres(&x, readop());
        _checkreg(&x);
        opcode =| x.value << 6;
        if (!checkop(',')) return error("a");
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
        if (!issym(op) || !checkop(',')) return error("x");
        expres(&x, readop());
        if (passno == 0) {
            op->type =| 32;
        } else if ((op->type & 31) == 0) {
            op->type =| 32;
            op->value = x.value;
        }
        break;
    case 29: /* jbr */
    case 30: /* jeq, jne, etc */
        len = op->type == 29 ? 4 : 6;
        expres(&x, readop());
        if (passno == 0) {
            if (x.type == *dotrel) {
                x.value =- *dot;
                if (-254 <= x.value && x.value < 0) {
                    len = 2;
                }
            }
            *dot =+ len;
        } else if (passno == 1) {
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
    case 27: /* estimated text */
    case 28: /* estimated data */
        if (passno == 0) break;
    case 20: /* reg */
    default:
        expres(&x, op);
        outw(x.type, x.value);
        break;
    }
}

op2b(opcode, opr1, opr2, rlimit)
{
    int i;
    if (rlimit != -1 && opr1 >= rlimit) _error("x");
    outw(0, opcode | (opr1 << 6) | opr2);
    for (i = 0; i < abufi; i =+ 3) {
        xsymbol = adrbuf[i + 2];
        outw(adrbuf[i + 1], adrbuf[i]);
    }
}

dobranch(this, opcode, min, max)
struct Op *this;
{
    int i;
    if (this->value < min || max < this->value
            || this->value & 1 /* (must) even */
            || this->type != *dotrel /* (must) same relocation as . */) {
        _error("b");
        outw(0, opcode);
    } else {
        outw(0, opcode | ((this->value >> 1) & 255));
    }
}

int savop;

_addres()
{
    return addres1(0);
}

addres1(astar)
{
    struct Op x;
    int op;
    switch (op = readop()) {
    case '(':
        expres(&x, readop());
        if (!checkop(')')) _error(")");
        _checkreg(&x);
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
        if (!checkop(')')) _error(")");
        _checkreg(&x);
        return x.value | 040;
    case '$':
        expres(&x, readop());
        adrbuf[abufi++] = x.value;
        adrbuf[abufi++] = x.type;
        adrbuf[abufi++] = xsymbol;
        return 027;
    case '*':
        if (astar) _error("*");
        return addres1(1) | 010;
    }
    expres(&x, op);
    if (checkop('(')) {
        adrbuf[abufi++] = x.value;
        adrbuf[abufi++] = x.type;
        adrbuf[abufi++] = xsymbol;
        expres(&x, readop());
        if (!checkop(')')) _error(")");
        _checkreg(&x);
        return x.value | 060;
    } else if (x.type == 20) {
        _checkreg(&x);
        return x.value;
    }
    x.value =- *dot + 4;
    if (abufi) x.value =- 2;
    adrbuf[abufi++] = x.value; /* index */
    adrbuf[abufi++] = -x.type; /* index reloc. */
    adrbuf[abufi++] = xsymbol; /* index global */
    return 067; /* address mode */
}

_checkreg(this)
struct Op *this;
{
    if (this->value > 7 || (this->value > 1 && this->type < 5)) {
        _error("a");
        this->type = this->value = 0;
    }
}

int brtabi, brlen, brdelt;
char brtab[];

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

/* checkrp()を汎用化（独自関数） */
checkop(ch)
{
    int op;
    if ((op = readop()) == ch) return 1;
    savop = op;
    return 0;
}

/* トークンがシンボルかどうかを判定（独自関数） */
issym(op)
{
    return op < 0 || 127 < op;
}
