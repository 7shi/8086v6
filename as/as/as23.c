/* translated from as23.s */

struct Op { char type, num; int value; };
struct Op curfbr[], *curfb[], *nxtfb[], *fbbufp;

int line, savop, numval, passno, *dotrel, *dot;
char fbfil;

_assem()
{
    struct Op x, *fb;
    int op, op2, num, i, t;

    for (;;) {
        op = readop();
        if (op == 4/*EOT*/) {
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op != ';') {
            if (op == 1) {
                op = 2;
                numval = getw();
            }
            op2 = readop();
            if (op2 == '=') {
                expres(&x, readop());
                if (!issym(op)) {
                    error("x");
                } else if (&op->value == dot) { /* test for dot */
                    x.type =& 31;
                    if (x.type != *dotrel) {
                        /* can't change relocation */
                        error(".");
                        if (passno == 0) *dotrel = 2;
                    } else {
                        if (passno == 0) {
                            op->type = (op->type & 32) | x.type;
                            op->value = x.type ? x.value : 0;
                        } else {
                            if (x.type == 4) { /* bss */
                                *dot = x.value;
                            } else if (*dot <= x.value) {
                                for (i = *dot; i < x.value; ++i) {
                                    outb(1, 0);
                                }
                            } else {
                                error(".");
                            }
                        }
                    }
                } else {
                    if (x.type == 32) error("r");
                    x.type =& 31;
                    if (x.type == 0) x.value = 0;
                    op->type =& 32;
                    op->type =| x.type;
                    op->value = x.value;
                }
            } else if (op2 == ':') {
                if (issym(op)) {
                    t = op->type & 31;
                    if (passno < 2) {
                        if (t == 27 || t == 28) {
                            op->type =& 32;
                        } else if (t) {
                            error("m");
                        }
                        op->type =| *dotrel;
                        op->value = *dot;
                    } else {
                        if (op->value != *dot) error("p");
                    }
                } else {
                    if (op == 1/*digit*/) {
                        num = fbcheck(numval);
                        curfbr[num].type  = *dotrel;
                        curfbr[num].value = *dot;
                        write(fbfil, dotrel, 1);
                        write(fbfil, &num  , 1);
                        write(fbfil, dot   , 2);
                    } else if (op == 2) {
                        fbadv(numval);
                        fb = curfb[numval];
                        fb->type  = *dotrel;
                        fb->value = *dot;
                    } else {
                        error("x");
                    }
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
    } while (fb->type >= 0 && fb->num != num);
    nxtfb[num] = fb;
}
