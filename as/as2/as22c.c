/* translated from as22.s */

int outmod, *dotrel, *dot, *dotdot, passno, *rseekp, *tseekp;
char *xsymbol, *usymtab, *txtp[], *relp[];

outw(value, type)
{
    int t;
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (*dot & 1) {
        error("o");
        outb(value, 0);
        return;
    }
    *dot =+ 2;
    if (!passno) return;
    t = type & 32767; /* get relative pc bit */
    if (t == 32) {
        /* external references */
        outmod = 0666; /* make nonexecutable */
        t = (xsymbol - usymtab) << 1;
        t =| 4; /* external relocation */
    } else {
        t =& ~32; /* clear any ext bits */
        if (t >= 5) {
            if (t == 27 || t == 28) {
                /* est. text, data */
                error("r");
            }
            t = 1; /* make absolute */
        }
        if (2 <= t && t <= 4) {
            if (type < 0) value =- *dotdot;
        } else if (type >= 0) {
            value =+ *dotdot;
        }
        if (--t < 0) t = 0;
    }
    putw(txtp, value);
    putw(relp, (t << 1) | (type < 0));
    *tseekp =+ 2;
    *rseekp =+ 2;
}

outb(value, type)
{
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (type > 1) error("r");
    if (passno) {
        if ((*dot & 1) == 0) {
            putw(txtp, value);
            putw(relp, 0);
            *rseekp =+ 2;
            *tseekp =+ 2;
        } else {
            txtp[0][-1] = value;
        }
    }
    ++*dot;
}

char argb[];
int line, errflg;

error(e)
char *e;
{
    int i, ln;
    char *p, buf[5];

    ++errflg;

    /* make nonexecutable */
    outmod = 0666;

    if (argb[0]) {
        printf("%s\n", argb);
        argb[0] = 0;
    }

    /* lineの値を10進数で表示 */
    ln = line;
    for (i = 0; i < 4; i++) {
        buf[3 - i] = '0' + (ln % 10);
        ln =/ 10;
    }
    buf[4] = 0;
    printf("%s %s\n", e, buf);
}
