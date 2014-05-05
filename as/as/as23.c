/* translated from as23.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int line, savop, passno, *_dotrel, *_dot, numval;
int header[];
char _symtab[];

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
                if (op == _symtab) { /* test for _dot */
                    x.type =& ~32;
                    if (x.type != *_dotrel) {
                        /* can't change relocation */
                        _error(".");
                    } else if (x.type == 4) { /* bss */
                        *_dot = x.value;
                    } else if (*_dot <= x.value) {
                        for (i = *_dot; i < x.value; ++i) {
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
                if (!_issym(op)) {
                    if (op == 2) {
                        fbadv(numval);
                        fb = curfb[numval];
                        fb->type  = *_dotrel;
                        fb->value = *_dot;
                    } else {
                        _error("x");
                    }
                } else if (!passno) {
                    t = op->type & 31;
                    if (t != 0 && t != 27 && t != 28) {
                        _error("m");
                    }
                    op->type =& ~31;
                    op->type =| *_dotrel;
                    op->value = *_dot;
                } else if (op->value != *_dot) {
                    _error("p");
                }
            } else {
                savop = op2;
                _opline(op);
            }
        }
        if (!passno) {
            /* txtsiz, datsiz, bsssiz */
            if (header[*_dotrel - 1] < *_dot) {
                header[*_dotrel - 1] = *_dot;
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
