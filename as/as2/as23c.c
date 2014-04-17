/* translated from as23.s */

struct Op { int type, value; };
struct { char cval; };

int line, savop, passno, *dotrel, *dot, brdelt, numval, txtsiz[];
int curfb[];
char symtab[];

assem()
{
    int r0, r1, r2, r3, r4, oldr4, i;
    do {
        r4 = readop();
        if (r4 == 5 || r4 == '<') {
            opline(r4);
        } else if (!checkeos(r4)) {
            oldr4 = r4;
            if (r4 == 1) {
                oldr4 = 2;
                numval = getw();
            }
            r4 = readop();
            if (r4 == '=') {
                r4 = expres(readop(), &r2, &r3);
                r1 = oldr4;
                if (r1 == symtab) { /* test for dot */
                    r3 =& ~32;
                    if (r3 != *dotrel) {
                        /* can't change relocation */
                        error(".");
                    } else if (r3 == 4) { /* bss */
                        *dot = r2;
                    } else if (*dot <= r2) {
                        for (i = *dot; i < r2; ++i) {
                            outb(0, 1);
                        }
                    } else {
                        error(".");
                    }
                } else {
                    if (r3 == 32) error("r");
                    r3 =& 31;
                    if (r3 == 0) r2 = 0;
                    r1->type =& ~31;
                    r1->type =| r3;
                    r1->value = r2;
                }
            } else if (r4 == ':') {
                r4 = oldr4;
                if (r4 < 128) {
                    if (r4 == 2) {
                        fbadv(numval);
                        r0 = curfb[numval];
                        r0->cval = *dotrel;
                        brdelt = r0->value - *dot;
                        r0->value = *dot;
                    } else {
                        error("x");
                    }
                } else if (!passno) {
                    r0 = r4->type & 31;
                    if (r0 != 0 && r0 != 27 && r0 != 28) {
                        error("m");
                    }
                    r4->type =& ~31;
                    r4->type =| *dotrel;
                    brdelt = r4->value - *dot;
                    r4->value = *dot;
                } else if (r4->value != *dot) {
                    error("p");
                }
            } else {
                savop = r4;
                r4 = oldr4;
                opline(r4);
            }
        }
        if (!passno) {
            if (txtsiz[*dotrel - 2] < *dot) {
                txtsiz[*dotrel - 2] = *dot;
            }
        }
        if (r4 == '\n') ++line;
    } while (r4 != 4/*EOT*/);
}

checkeos(r4)
{
    return r4 == '\n' || r4 == ';' || r4 == 4/*EOT*/;
}

int nxtfb[], *fbbufp;

fbadv(r4)
{
    int *r1;
    r1 = nxtfb[r4];
    curfb[r4] = r1;
    if (r1 == 0) {
        r1 = fbbufp - 2;
    }
    do {
        r1 =+ 2;
        if (*r1 >> 9 == r4) break;
    } while (*r1 >= 0);
    nxtfb[r4] = r1;
}
