/* translated from as16.s */

struct Op { int type, value; };

int *dot, *dotrel, savdot[], savop, ifflg, numval;

opline(op)
{
    struct Op x;
    int len;

    if (op == '<') {
        *dot =+ numval;
        return;
    } else if (0 <= op && op < 128) {
        expres(&x, op);
        *dot =+ 2;
        return;
    }

    switch (op->type) {
    case  5: /* map fop freg,fdst to double */
    case 10: /* map fld/fst to double */
    case 11: /* double operand (mov) */
    case 12: /* map fop fsrc,freg to double */
    case 24: /* map mul s,r to double */
    case  7: /* jsr */
        /* double */
        addres(readop());
        if (!checkop(',')) {
            error("a");
            break;
        }
    case 13: /* single operand */
        addres(readop());
        *dot =+ 2;
        break;
    case 14: /* .byte */
        do {
            expres(&x, readop());
            *dot =+ 1;
        } while (checkop(','));
        break;
    case 15: /* < (.ascii) */
        readop();
        *dot =+ numval;
        break;
    case 16: /* .even */
        *dot = (*dot + 1) & ~1;
        break;
    case 17: /* .if */
        expres(&x, readop());
        if (x.type  == 0) error("U");
        if (x.value == 0) ifflg =+ 1;
        break;
    case 18: /* endif */
        break;
    case 19: /* .globl */
        do {
            if ((op = readop()) < 128) {
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
            break;
        }
        expres(&x, readop());
        *dot =+ 2;
        break;
    case 26: /* .common */
        if ((op = readop()) < 128 || !checkop(',')) {
            error("x");
            break;
        }
        op->type =| 32;
        expres(&x, readop());
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
    case 27: /* estimated text */
    case 28: /* estimated data */
        op = readop();
    default:
        expres(&x, op);
        *dot =+ 2;
        break;
    }
}

addres(op)
{
    struct Op x;
    int num;

    switch (op) {
    case '(':
        expres(&x, readop());
        checkreg(&x);
        if (!checkop(')')) error(")");
        if ((op = readop()) == '+') return 0;
        savop = op;
        return 2;
    case '-':
        if ((op = readop()) == '(') {
            expres(&x, readop());
            checkreg(&x);
            if (!checkop(')')) error(")");
        } else {
            savop = op;
            savop = getx('-');
        }
        return 0;
    case '$':
        expres(&x, readop());
        *dot =+ 2;
        return 0;
    case '*':
        if ((op = readop()) == '*') {
            error("*");
        }
        num = addres(op);
        *dot =+ num;
        return num;
    }
    savop = getx(op);
    return 0;
}

getx(op)
{
    struct Op x;

    expres(&x, op);
    if ((op = readop()) == '(') {
        expres(&x, readop());
        checkreg(&x);
        if (!checkop(')')) error(")");
        op = readop();
        *dot =+ 2;
    } else if (x.type == 20) {
        /* register type */
        checkreg(&x);
    } else {
        *dot =+ 2;
    }
    return op;
}

checkreg(this)
struct Op *this;
{
    if (this->value > 7 || (this->type != 1 && this->type <= 4)) {
        error("a");
    }
}

checkop(ch)
{
    int op;
    if ((op = readop()) == ch) return 1;
    savop = op;
    return 0;
}
