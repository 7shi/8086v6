/* translated from as23.s */

struct Op { char type, num; int value; };
extern struct Op *curfb[], *nxtfb[], *fbbufp;

extern int line, savop, passno, *dotrel, *dot, numval;
extern int header[];
extern char argb[];

assem()
{
    struct Op x, *fb;
    int t, op, op2, i, w;
    for (;;) {
        op = readop();
        if (op == 4/*EOT*/) {
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op == 5/*file name*/) {
            /* file name */
            line = 1;
            memset(argb, 0, 22);
            for (i = 0;; ++i) {
                w = getw();
                if (w < 0) break;
                if (i < 21) argb[i] = w;
            }
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
                if (issym(op)) {
                    if (passno < 2) {
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
                } else if (op == 1) {
                    fbadv(numval);
                    fb = curfb[numval];
                    fb->type  = *dotrel;
                    fb->value = *dot;
                } else {
                    error("x");
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
