/* translated from as23.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int line, savop, passno, *dotrel, *dot, numval;
int header[];

_assem()
{
    struct Op x, *fb;
    int t, op, op2, i;
    for (;;) {
        op = _readop();
        if (op == 4/*EOT*/) {
            break;
        } else if (op == '\n') {
            ++line;
        } else if (op == 5/*file name*/ || op == '<'/*string*/) {
            _opline(op);
        } else if (op != ';') {
            if (op == 1) {
                op = 2;
                numval = getw();
            }
            op2 = _readop();
            if (op2 == '=') {
                _expres(&x, _readop());
                if (&op->value == dot) { /* test for dot */
                    x.type =& ~32;
                    if (x.type != *dotrel) {
                        /* can't change relocation */
                        _error(".");
                    } else if (x.type == 4) { /* bss */
                        *dot = x.value;
                    } else if (*dot <= x.value) {
                        for (i = *dot; i < x.value; ++i) {
                            outb(1, 0);
                        }
                    } else {
                        _error(".");
                    }
                } else {
                    if (x.type == 32) _error("r");
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
                        fb->type  = *dotrel;
                        fb->value = *dot;
                    } else {
                        _error("x");
                    }
                } else if (!passno) {
                    t = op->type & 31;
                    if (t != 0 && t != 27 && t != 28) {
                        _error("m");
                    }
                    op->type =& ~31;
                    op->type =| *dotrel;
                    op->value = *dot;
                } else if (op->value != *dot) {
                    _error("p");
                }
            } else {
                savop = op2;
                _opline(op);
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
