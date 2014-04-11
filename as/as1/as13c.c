/* translated from as13.s */

struct Op { int type, value; };

char *savop, fbfil, curfbr[];
int ifflg, line, numval, curfb[];
int *dotrel, *dot;

assem() {
    struct Op x;
    int op, op2, num;

    for (;;) {
        op = readop();
        if (!checkeos(op)) {
            if (ifflg) {
                if (op >= 128) {
                    if (op->type == 17/*if*/) {
                        ++ifflg;
                    } else if (op->type == 18/*endif*/) {
                        --ifflg;
                    }
                }
                continue;
            }
            op2 = readop();
            if (op2 == '=') {
                expres(&x, readop());
                if (op < 128) {
                    error("x");
                } else if (op == dotrel && (x.type & 31) != *dotrel) {
                    error(".");
                    *dotrel = 2;
                } else {
                    x.type =& 31;
                    op->type = (op->type & 32) | x.type;
                    op->value = x.type ? x.value : 0;
                }
            } else if (op2 == ':') {
                if (op >= 128) {
                    if (op->type & 31) error("m");
                    op->type =| *dotrel;
                    op->value = *dot;
                } else if (op == 1/*digit*/) {
                    num = fbcheck(numval);
                    curfbr[num] = *dotrel;
                    curfb [num] = *dot;
                    num =<< 1;
                    write(fbfil, dotrel, 1);
                    write(fbfil, &num  , 1);
                    write(fbfil, dot   , 2);
                } else {
                    error("x");
                }
                continue;
            } else {
                savop = op2;
                opline(op);
            }
            op = readop();
        }
        if (op == 4/*EOT*/) {
            if (ifflg) error("x");
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op != ';') {
            error("x");
            while (!checkeos(op)) {
                op = readop();
            }
        }
    }
}

fbcheck(n) {
    if (n <= 9) return n;
    error("f");
    return 0;
}

checkeos(op) {
    return op == '\n' || op == ';' || op == 4/*EOT*/;
}
