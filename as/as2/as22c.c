/* translated from as22.s */

int outmod, *dotrel, *dot, *dotdot, passno, *rseekp, *tseekp;
char *xsymbol, *usymtab, *txtp[], *relp[];

outw(r2, r3)
{
    int tmp;
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (*dot & 1) {
        error("o");
        outb(r2, 0);
        return;
    }
    *dot =+ 2;
    if (!passno) return;
    tmp = r3 < 0;
    r3 =& 32767; /* get relative pc bit */
    if (r3 == 32) {
        /* external references */
        outmod = 0666; /* make nonexecutable */
        r3 = (xsymbol - usymtab) << 1;
        r3 =| 4; /* external relocation */
    } else {
        r3 =& ~32; /* clear any ext bits */
        if (r3 >= 5) {
            if (r3 == 27 || r3 == 28) {
                /* est. text, data */
                error("r");
            }
            r3 = 1; /* make absolute */
        }
        if (2 <= r3 && r3 <= 4) {
            if (tmp) r2 =- *dotdot;
        } else if (!tmp) {
            r2 =+ *dotdot;
        }
        if (--r3 < 0) r3 = 0;
    }
    putw(txtp, r2);
    putw(relp, (r3 << 1) | tmp);
    *tseekp =+ 2;
    *rseekp =+ 2;
}

outb(r2, r3)
{
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (r3 > 1) error("r");
    if (passno) {
        if ((*dot & 1) == 0) {
            putw(txtp, r2);
            putw(relp, 0);
            *rseekp =+ 2;
            *tseekp =+ 2;
        } else {
            txtp[0][-1] = r2;
        }
    }
    ++*dot;
}

char argb[];
int line, errflg;

error(r5)
char *r5;
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
    printf("%s %s\n", r5, buf);
}
