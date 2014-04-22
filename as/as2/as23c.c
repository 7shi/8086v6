/* translated from as23.s */

struct Op { int type, value; };

int line, savop, passno, *dotrel, *dot, brdelt, numval, *txtsiz;
int curfb[];
char symtab[];

assem()
{
    struct Op x;
    int t, op, oldop, i;
    char *fb;
    do {
        op = readop();
        if (op == 5 || op == '<') {
            opline(op);
        } else if (!checkeos(op)) {
            oldop = op;
            if (op == 1) {
                oldop = 2;
                numval = getw();
            }
            op = readop();
            if (op == '=') {
                expres(&x, readop());
                op = readop();
                if (oldop == symtab) { /* test for dot */
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
                    oldop->type =& ~31;
                    oldop->type =| x.type;
                    oldop->value = x.value;
                }
            } else if (op == ':') {
                op = oldop;
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
                savop = op;
                op = oldop;
                opline(op);
            }
        }
        if (!passno) {
            if (txtsiz[*dotrel - 2] < *dot) {
                txtsiz[*dotrel - 2] = *dot;
            }
        }
        if (op == '\n') ++line;
    } while (op != 4/*EOT*/);
}

checkeos(op)
{
    return op == '\n' || op == ';' || op == 4/*EOT*/;
}

int nxtfb[], *fbbufp;

fbadv(op)
{
    int *fb;
    fb = nxtfb[op];
    curfb[op] = fb;
    if (fb == 0) {
        fb = fbbufp - 2;
    }
    do {
        fb =+ 2;
        if (*fb >> 9 == op) break;
    } while (*fb >= 0);
    nxtfb[op] = fb;
}
