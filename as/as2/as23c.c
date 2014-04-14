/* translated from as23.s */

int line, savop, passno, dot, dotrel, brdelt, numval, txtsiz[];
int curfb[];
char symtab[];
struct { char cval; };
struct { int ival; };

assem()
{
    int r0, r1, r2, r3, r4, sp;
assem0:
    r4 = readop();
    if (r4 != 5 && r4 != '<') {
        if (checkeos(r4)) goto ealoop;
        sp = r4;
        if (r4 == 1) {
            sp = 2;
            r4 = getw();
            numval = r4;
        }
        r4 = readop();
        if (r4 == '=') goto assem4;
        if (r4 == ':') goto assem1;
        savop = r4;
        r4 = sp;
    }
    opline(r4);
dotmax:
    if (passno) goto ealoop;
    r0 = dotrel;
    if (txtsiz[r0 - 2] < dot) {
        txtsiz[r0 - 2] = dot;
    }
    goto ealoop;
assem1:
    r4 = sp;
    if (r4 < 128) {
        if (r4 == 2) goto assem3;
        error("x");
        goto assem0;
    }
    if (!passno) {
        r0 = r4->cval;
        r0 =& 31;
        if (r0 != 0 && r0 != 27 && r0 != 28) {
            error("m");
        }
        r4->ival =& ~31;
        r4->ival =| dotrel;
        brdelt = (r4 + 2)->ival;
        brdelt =- dot;
        (r4 + 2)->ival = dot;
        goto assem0;
    }
    if ((r4 + 2)->ival == dot) goto assem0;
    error("p");
    goto assem0;
assem3:
    r4 = numval;
    fbadv(r4);
    r0 = curfb[r4];
    r0->cval = dotrel;
    brdelt = (r0 + 2)->ival;
    brdelt =- dot;
    (r0 + 2)->ival = dot;
    goto assem0;
assem4:
    r4 = readop();
    r4 = expres(r4, &r2, &r3);
    r1 = sp;
    if (r1 == symtab) { /* test for dot */
        r3 =& ~32;
        if (r3 == dotrel) { /* can't change relocation */
            if (r3 == 4) { /* bss */
                dot = r2;
                goto dotmax;
            }
            r2 =- dot;
            if (r2 >= 0) {
                sp = r2;
                while (--sp >= 0) {
                    outb(0, 1);
                }
                goto dotmax;
            }
        }
        error(".");
        goto ealoop;
    }
    if (r3 == 32) error("r");
    r1->ival =& ~31;
    r3 =& 31;
    if (r3 == 0) r2 = 0;
    r1->cval =| r3;
    (r1 + 2)->ival = r2;

ealoop:
    if (r4 == '\n') {
        ++line;
        goto assem0;
    } else if (r4 != 4/*EOT*/) {
        goto assem0;
    }
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
