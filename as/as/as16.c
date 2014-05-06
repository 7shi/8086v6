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
    case  5: /* map fop freg,fdst to double */
    case  7: /* jsr */
    case 10: /* map fld/fst to double */
    case 11: /* double operand (mov) */
    case 12: /* map fop fsrc,freg to double */
    case 24: /* map mul s,r to double */
        /* double */
        addres();
        if (!checkop(',')) {
            error("a");
            break;
        }
    case 13: /* single operand */
        addres();
        *dot =+ 2;
        break;
    case 14: /* .byte */
        do {
            expres(&x, readop());
            ++*dot;
        } while (checkop(','));
        break;
    case 15: /* < (.ascii) */
        /* not used */
        break;
    case 16: /* .even */
        *dot = (*dot + 1) & ~1;
        break;
    case 17: /* .if */
        expres(&x, readop());
        if (x.type  == 0) error("U");
        if (x.value == 0) ++ifflg;
        break;
    case 18: /* endif */
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
    case 23: /* .bss */
        savdot[*dotrel - 2] = *dot;
        *dot = savdot[op->type - 21];
        *dotrel = op->type - 19;
        break;
    case 25: /* sob */
        expres(&x, readop());
        if (!checkop(',')) {
            error("a");
        } else {
            expres(&x, readop());
            *dot =+ 2;
        }
        break;
    case 26: /* .common */
        if (!issym(op = readop()) || !checkop(',')) {
            error("x");
        } else {
            op->type =| 32;
            expres(&x, readop());
        }
        break;
    case 27: /* estimated text */
    case 28: /* estimated data */
        /* used in as2 only */
        break;
    case 29: /* jbr */
    case 30: /* jeq, etc */
        len = op->type == 29 ? 4 : 6;
        expres(&x, readop());
        if (x.type == *dotrel) {
            x.value =- *dot;
            if (-254 <= x.value && x.value < 0) {
                len = 2;
            }
        }
        *dot =+ len;
        break;
    case  6: /* branch */
    case  8: /* rts */
    case  9: /* sys */
        op = readop();
    default:
        expres(&x, op);
        *dot =+ 2;
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
