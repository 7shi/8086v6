/* translated from as16.s */

int *dot, *dotrel, savdot[], savop, ifflg, numval;
struct { int type, val; };

opline(op)
{
    int type, num, r3, len;

    if (op == '<') {
        *dot =+ numval;
        return readop();
    } else if (0 <= op && op < 128) {
        num = expres(op, &r3);
        *dot =+ 2;
        return readop();
    }

    type = op->type;
    if (type != 20/*register*/ && 5 <= type && type <= 30) {
        op = readop();
    }

    switch (type) {
    case  5: /* map fop freg,fdst to double */
    case 10: /* map fld/fst to double */
    case 11: /* double operand (mov) */
    case 12: /* map fop fsrc,freg to double */
    case 24: /* map mul s,r to double */
    case  7: /* jsr */
        /* double */
        addres(op);
        if ((op = readop()) != ',') {
            error("a");
            return op;
        }
        op = readop();
    case 13: /* single operand */
        addres(op);
        *dot =+ 2;
        return readop();
    case 14: /* .byte */
        for (;;) {
            num = expres(op, &r3);
            *dot =+ 1;
            if ((op = readop()) != ',') break;
            op = readop();
        }
        return op;
    case 15: /* < (.ascii) */
        *dot =+ numval;
        return readop();
    case 16: /* .even */
        *dot =+ 1;
        *dot =& ~1;
        return op;
    case 17: /* .if */
        num = expres(op, &r3);
        if (r3 == 0) error("U");
        if (num == 0) ifflg =+ 1;
        return readop();
    case 18: /* endif */
        return op;
    case 19: /* .globl */
        while (op >= 128) {
            op->type =| 32;
            op = readop();
            if (op != ',') break;
            op = readop();
        }
        return op;
    case 21: /* .text */
    case 22: /* .data */
    case 23: /* .bss */
        savdot[*dotrel-2] = *dot;
        *dot = savdot[type-21];
        *dotrel = type - 19;
        return op;
    case 25: /* sob */
        num = expres(op, &r3);
        if ((op = readop()) != ',') error("a");
        op = readop();
        break;
    case 26: /* .common */
        if (op >= 128) {
            op->type =| 32;
            op = readop();
            if (op == ',') {
                num = expres(readop(), &r3);
                return readop();
            }
        }
        error("x");
        return op;
    case 29: /* jbr */
    case 30: /* jeq, etc */
        len = type == 29 ? 4 : 6;
        num = expres(op, &r3);
        if (r3 == *dotrel) {
            num =- *dot;
            if (-254 <= num && num < 0) {
                len = 2;
            }
        }
        *dot =+ len;
        return readop();
    }
    num = expres(op, &r3);
    *dot =+ 2;
    return readop();
}

addres(op)
{
    int num, r3;

    switch (op) {
    case '(':
        num = expres(readop(), &r3);
        op = checkrp();
        checkreg(num, r3);
        if (op == '+') return 0;
        savop = op;
        return 2;
    case '-':
        op = readop();
        if (op == '(') {
            num = expres(readop(), &r3);
            op = checkrp();
            checkreg(num, r3);
            savop = op;
        } else {
            savop = op;
            savop = getx('-');
        }
        return 0;
    case '$':
        num = expres(readop(), &r3);
        *dot =+ 2;
        return 0;
    case '*':
        op = readop();
        if (op == '*') {
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
    int r, r3;

    r = expres(op, &r3);
    if ((op = readop()) == '(') {
        r = expres(readop(), &r3);
        checkreg(r, r3);
        op = checkrp();
        *dot =+ 2;
    } else if (r3 == 20) {
        /* register type */
        checkreg(r, r3);
    } else {
        *dot =+ 2;
    }
    return op;
}

checkreg(r, r3)
{
    if (r > 7 || (r3 != 1 && r3 <= 4)) {
        error("a");
    }
}

checkrp()
{
    int op;
    op = readop();
    if (op == ')') {
        op = readop();
    } else {
        error(")");
    }
    return op;
}
