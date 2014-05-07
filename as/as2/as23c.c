/* translated from as23.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int line, savop, passno, *dotrel, *dot, numval;
int header[];

assem()
{
    struct Op x, *fb;
    int t, op, op2, i;
    for (;;) {
        op = readop();
        if (op == 4/*EOT*/) {
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op == 5/*file name*/ || op == '<'/*string*/) {
            opline(op);
        } else if (op != ';') {
            op2 = readop();
            if (op2 == '=') {
                expres(&x, readop());
                if (&op->value == dot) { /* test for dot */
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
                    if (op == 1) {
                        fbadv(numval);
                        fb = curfb[numval];
                        fb->type  = *dotrel;
                        fb->value = *dot;
                    } else {
                        error("x");
                    }
                } else if (passno < 2) {
                    t = op->type & 31;
                    if (t != 0 && t != 27 && t != 28) {
                        error("m");
                    }
                    op->type =& ~31;
                    op->type =| *dotrel;
                    op->value = *dot;
                } else if (op->value != *dot) {
                    error("p");
                }
            } else {
                savop = op2;
                opline(op);
            }
        }
    }
}

fbadv(num)
{
    struct Op *fb;
    fb = curfb[num] = nxtfb[num];
    if (!fb) fb = fbbufp - 1;
    do {
        ++fb;
    } while (fb->type >= 0 && (fb->num >> 1) != num);
    nxtfb[num] = fb;
}
