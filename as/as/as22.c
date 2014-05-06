/* translated from as22.s */

int outmod, *dotrel, *dot, *dotdot, passno, tseeks[], rseeks[];
char *xsymbol, *usymtab, *txtp[], *relp[];

outw(type, value)
{
    int t;
    if (*dotrel == 4) { /* test bss mode */
        _error("x");
        return;
    }
    if (*dot & 1) {
        _error("o");
        outb(0, value);
        return;
    }
    *dot =+ 2;
    if (passno < 2) return;
    t = abs(type); /* type < 0: relative pc */
    if (t == 32) {
        /* external references */
        outmod = 0666; /* make nonexecutable */
        t = (xsymbol - usymtab) << 1;
        t =| 4; /* external relocation */
    } else {
        t =& 31; /* clear any ext bits */
        if (t >= 5) {
            if (t == 27 || t == 28) {
                /* est. text, data */
                _error("r");
            }
            t = 1; /* make absolute */
        }
        if (t < 2 || t > 4) {
            if (type < 0) value =- *dotdot;
        } else {
            if (type >= 0) value =+ *dotdot;
        }
        if (--t < 0) t = 0;
    }
    _putw(txtp, value);
    _putw(relp, (t << 1) | (type < 0));
    tseeks[*dotrel - 2] =+ 2;
    rseeks[*dotrel - 2] =+ 2;
}

outb(type, value)
{
    if (*dotrel == 4) { /* test bss mode */
        _error("x");
        return;
    }
    if (type > 1) _error("r");
    if (passno == 2) {
        if ((*dot & 1) == 0) {
            _putw(txtp, value);
            _putw(relp, 0);
            tseeks[*dotrel - 2] =+ 2;
            rseeks[*dotrel - 2] =+ 2;
        } else {
            txtp[0][-1] = value;
        }
    }
    ++*dot;
}

char argb[];
int line, errflg;

_error(e)
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
