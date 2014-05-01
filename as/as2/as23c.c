/* translated from as23.s */

struct Op { int type, value; };

int line, savop, passno, *dotrel, *dot, brdelt, numval;
int header[], curfb[];
char symtab[];

assem()
{
    struct Op x;
    int t, op, op2, i;
    char *fb;
    for (;;) {
        op = readop();
        if (op == 4/*EOT*/) {
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op == 5/*file name*/ || op == '<'/*string*/) {
            opline(op);
        } else if (op != ';') {
            if (op == 1) {
                op = 2;
                numval = getw();
            }
            op2 = readop();
            if (op2 == '=') {
                expres(&x, readop());
                if (op == symtab) { /* test for dot */
                    x.type =& ~32;
                    if (x.type != *dotrel) {
                        /* can't change relocation */
                        error(".");
                    } else if (x.type == 4) { /* bss */
                        *dot = x.value;
                    } else if (*dot <= x.value) {
                        for (i = *dot; i < x.value; ++i) {
                            outb(1, 0);
                        }
                    } else {
                        error(".");
                    }
                } else {
                    if (x.type == 32) error("r");
                    x.type =& 31;
                    if (x.type == 0) x.value = 0;
                    op->type =& ~31;
                    op->type =| x.type;
                    op->value = x.value;
                }
            } else if (op2 == ':') {
                if (!issym(op)) {
                    if (op == 2) {
                        fbadv(numval);
                        fb = curfb[numval];
                        *fb = *dotrel;
                        brdelt = fb->value - *dot;
                        fb->value = *dot;
                    } else {
                        error("x");
                    }
                } else if (!passno) {
                    t = op->type & 31;
                    if (t != 0 && t != 27 && t != 28) {
                        error("m");
                    }
                    op->type =& ~31;
                    op->type =| *dotrel;
                    brdelt = op->value - *dot;
                    op->value = *dot;
                } else if (op->value != *dot) {
                    error("p");
                }
            } else {
                savop = op2;
                opline(op);
            }
        }
        if (!passno) {
            /* txtsiz, datsiz, bsssiz */
            if (header[*dotrel - 1] < *dot) {
                header[*dotrel - 1] = *dot;
            }
        }
    }
}

int nxtfb[], *fbbufp;

fbadv(op)
{
    int *fb;
    fb = nxtfb[op];
    curfb[op] = fb;
    if (fb == 0) fb = fbbufp - 2;
    do {
        fb =+ 2;
    } while ((*fb >> 9) != op && *fb >= 0);
    nxtfb[op] = fb;
}
