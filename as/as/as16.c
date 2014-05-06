/* translated from as16.s */

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
        if (!checkop(',')) {
            error("a");
            break;
        }
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
        if (!checkop(',')) {
            error("a");
            break;
        }
        op2b(opcode, x.value, _addres(), -1);
        break;
    case 8: /* rts */
        expres(&x, readop());
        _checkreg(&x);
        outw(x.type, opcode | x.value);
        break;
    case 9: /* sys, emt etc */
        expres(&x, readop());
        if (x.value >= 64 || x.type > 1) _error("a");
        outw(x.type, opcode | x.value);
        break;
    case 10: /* movf */
        opr = _addres();
        if (!checkop(',')) {
            error("a");
            break;
        }
        if (opr >= 4) {
            /* see if source is fregister */
            op2b(opcode, _addres(), opr, 4);
        } else {
            op2b(0174000, opr, _addres(), -1);
        }
        break;
    case 11: /* double */
        opr = _addres();
        if (!checkop(',')) {
            error("a");
            break;
        }
        op2b(opcode, opr, _addres(), -1);
        break;
    case 12: /* flop freg,fsrc */
        opr = _addres();
        if (!checkop(',')) {
            error("a");
            break;
        }
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
        if (!checkop(',')) {
            error("a");
            break;
        }
        op2b(opcode, _addres(), opr, 010);
        break;
    case 25: /* sob */
        expres(&x, readop());
        _checkreg(&x);
        opcode =| x.value << 6;
        if (!checkop(',')) {
            error("a");
            break;
        }
        expres(&x, readop());
        if (passno < 2) {
            *dot =+ 2;
        } else {
            x.value = (*dot + 2) - x.value; /* back only */
            dobranch(&x, opcode, 0, 126);
        }
        break;
    case 26: /* .comm */
        if (!issym(op = readop()) || !checkop(',')) {
            error("x");
            break;
        }
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

addres()
{
    struct Op x;
    int op, num;

    switch (op = readop()) {
    case '(':
        expres(&x, readop());
        checkreg(&x);
        if (!checkop(')')) error(")");
        if (checkop('+')) break;
        return 2;
    case '-':
        if (checkop('(')) {
            expres(&x, readop());
            checkreg(&x);
            if (!checkop(')')) error(")");
        } else {
            getx(op);
        }
        break;
    case '$':
        expres(&x, readop());
        *dot =+ 2;
        break;
    case '*':
        if (checkop('*')) error("*");
        *dot =+ addres();
        break;
    default:
        getx(op);
        break;
    }
    return 0;
}

getx(op)
{
    struct Op x;

    expres(&x, op);
    if (checkop('(')) {
        expres(&x, readop());
        checkreg(&x);
        if (!checkop(')')) error(")");
        *dot =+ 2;
    } else if (x.type == 20) {
        /* register type */
        checkreg(&x);
    } else {
        *dot =+ 2;
    }
}

checkreg(this)
struct Op *this;
{
    if (this->value > 7 || (this->type != 1 && this->type <= 4)) {
        error("a");
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

/* トークンがシンボルかどうかを判定（独自関数） */
issym(op)
{
    return op < 0 || 127 < op;
}
