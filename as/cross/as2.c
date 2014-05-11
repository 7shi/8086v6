extern int outmod, *dotrel, *dot, *dotdot, passno, tseeks[], rseeks[];
extern char *xsymbol, *usymtab, *txtp[], *relp[];

outw(type, value)
{
    int t;
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (*dot & 1) {
        error("o");
        outb(0, value);
        return;
    }
    *dot += 2;
    if (passno < 2) return;
    t = abs(type); /* type < 0: relative pc */
    if (t == 32) {
        /* external references */
        outmod = 0666; /* make nonexecutable */
        t = (xsymbol - usymtab) << 1;
        t |= 4; /* external relocation */
    } else {
        t &= 31; /* clear any ext bits */
        if (t >= 5) {
            if (t == 27 || t == 28) {
                /* est. text, data */
                error("r");
            }
            t = 1; /* make absolute */
        }
        if (t < 2 || t > 4) {
            if (type < 0) value -= *dotdot;
        } else {
            if (type >= 0) value += *dotdot;
        }
        if (--t < 0) t = 0;
    }
    aputw(txtp, value);
    aputw(relp, (t << 1) | (type < 0));
    tseeks[*dotrel - 2] += 2;
    rseeks[*dotrel - 2] += 2;
}

outb(type, value)
{
    if (*dotrel == 4) { /* test bss mode */
        error("x");
        return;
    }
    if (type > 1) error("r");
    if (passno == 2) {
        if ((*dot & 1) == 0) {
            aputw(txtp, value);
            aputw(relp, 0);
            tseeks[*dotrel - 2] += 2;
            rseeks[*dotrel - 2] += 2;
        } else {
            txtp[0][-1] = value;
        }
    }
    ++*dot;
}

extern char argb[], **curarg;
extern int line, errflg;

error(e)
char *e;
{
    int i, ln;
    char buf[5];

    ++errflg;

    if (passno == 0) {
        if (*curarg) {
            printf("%s\n", *curarg);
            *curarg = 0;
        }
    } else {
        if (argb[0]) {
            printf("%s\n", argb);
            argb[0] = 0;
        }
        /* make nonexecutable */
        outmod = 0666;
    }

    /* lineの値を10進数で表示 */
    ln = line;
    for (i = 0; i < 4; i++) {
        buf[3 - i] = '0' + (ln % 10);
        ln /= 10;
    }
    buf[4] = 0;
    printf("%s %s\n", e, buf);
}
