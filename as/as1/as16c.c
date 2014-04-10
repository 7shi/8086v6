/* translated from as16.s */

int *dot, *dotrel, savdot[], savop, ifflg, numval;
struct { int type, val; };

opline(op)
{
    int num, type, len;

    if (op == '<') {
        *dot =+ numval;
        return;
    } else if (0 <= op && op < 128) {
        expres(op, &type);
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
            expres(readop(), &type);
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
        num = expres(readop(), &type);
        if (type == 0) error("U");
        if (num == 0) ifflg =+ 1;
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
        expres(readop(), &type);
        if (!checkop(',')) {
            error("a");
            break;
        }
        expres(readop(), &type);
        *dot =+ 2;
        break;
    case 26: /* .common */
        if ((op = readop()) < 128 || !checkop(',')) {
            error("x");
            break;
        }
        op->type =| 32;
        expres(readop(), &type);
        break;
    case 29: /* jbr */
    case 30: /* jeq, etc */
        len = op->type == 29 ? 4 : 6;
        num = expres(readop(), &type);
        if (type == *dotrel) {
            num =- *dot;
            if (-254 <= num && num < 0) {
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
        expres(op, &type);
        *dot =+ 2;
        break;
    }
}

addres(op)
{
    int num, type;

    switch (op) {
    case '(':
        num = expres(readop(), &type);
        checkreg(num, type);
        if (!checkop(')')) error(")");
        if ((op = readop()) == '+') return 0;
        savop = op;
        return 2;
    case '-':
        if ((op = readop()) == '(') {
            num = expres(readop(), &type);
            checkreg(num, type);
            if (!checkop(')')) error(")");
        } else {
            savop = op;
            savop = getx('-');
        }
        return 0;
    case '$':
        expres(readop(), &type);
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
    int r, type;
    r = expres(op, &type);
    if ((op = readop()) == '(') {
        r = expres(readop(), &type);
        checkreg(r, type);
        if (!checkop(')')) error(")");
        op = readop();
        *dot =+ 2;
    } else if (type == 20) {
        /* register type */
        checkreg(r, type);
    } else {
        *dot =+ 2;
    }
    return op;
}

checkreg(r, type)
{
    if (r > 7 || (type != 1 && type <= 4)) {
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
