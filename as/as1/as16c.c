/* translated from as16.s */

int *dot, *dotrel, savdot[], savop, ifflg, numval;
struct { int type, val; };

opline(op)
{
    int r0, num, r3, sp;

    if (op == '<') {
        *dot =+ numval;
        return readop();
    } else if (0 <= op && op < 128) {
        num = expres(op, &r3);
        *dot =+ 2;
        return readop();
    }

    r0 = op->type;
    if (r0 != 20 && 5 <= r0 && r0 <= 30) op = readop();

    switch (r0) {
    case  5: /* map fop freg,fdst to double */
    case 10: /* map fld/fst to double */
    case 11:
    case 12: /* map fop fsrc,freg to double */
    case 24: /* map mul s,r to double */
    case  7:
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
    case 21:
    case 22:
    case 23:
        savdot[*dotrel-2] = *dot;
        *dot = savdot[r0-21];
        *dotrel = r0 - 19;
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
        sp = r0 == 29 ? 4 : 6;
        num = expres(op, &r3);
        if (r3 == *dotrel) {
            num =- *dot;
            if (-254 <= num && num < 0) {
                sp = 2;
            }
        }
        *dot =+ sp;
        return readop();
    }
    num = expres(op, &r3);
    *dot =+ 2;
    return readop();
}

addres(r4)
{
    int num, r3;

    switch (r4) {
    case '(':
        num = expres(readop(), &r3);
        r4 = checkrp(readop());
        checkreg(num, r3);
        if (r4 == '+') return 0;
        savop = r4;
        return 2;
    case '-':
        r4 = readop();
        if (r4 == '(') {
            num = expres(readop(), &r3);
            r4 = checkrp(readop());
            checkreg(num, r3);
            savop = r4;
        } else {
            savop = r4;
            savop = getx('-');
        }
        return 0;
    case '$':
        num = expres(readop(), &r3);
        *dot =+ 2;
        return 0;
    case '*':
        r4 = readop();
        if (r4 == '*') {
            error("*");
        }
        num = addres(r4);
        *dot =+ num;
        return num;
    }
    savop = getx(r4);
    return 0;
}

getx(r4)
{
    int r2, r3;

    r2 = expres(r4, &r3);
    if ((r4 = readop()) == '(') {
        r2 = expres(readop(), &r3);
        checkreg(r2, r3);
        r4 = checkrp(readop());
        *dot =+ 2;
    } else if (r3 == 20) {
        /* register type */
        checkreg(r2, r3);
    } else {
        *dot =+ 2;
    }
    return r4;
}

checkreg(r2, r3)
{
    if (r2 <= 7) {
        if (r3 == 1 || r3 > 4) {
            return ;
        }
    }
    error("a");
    return ;
}

checkrp(r4)
{
    if (r4 == ')') {
        r4 = readop();
    } else {
        error(")");
    }
    return r4;
}
