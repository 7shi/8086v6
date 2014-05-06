/* translated from as21.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int outmod 0777;
int savdot[], datbase, bssbase, ibufc;
int *dotrel, *dot, *dotdot, brtabi, passno;
int header[], *txtmagic, *txtsiz, *datsiz, *bsssiz, *symsiz;
int *txtseek, *datseek, *trelseek, *drelseek, symseek;
char fin, *txtp[], *relp[], *atmp1, *atmp2, *atmp3;
char *usymtab, *endtable, *memend;

/* set up sizes and origins */
go()
{
    int t, *p, i, w;

    /* read in symbol table */
    p = usymtab = memend = sbrk(0);
    fin = ofile(atmp3);
    while (getw() != 4/*EOT*/) {
        setbrk(p + 2);
        *symsiz =+ 12; /* count symbols */
        getw();
        getw();
        getw();
        w = getw();
        t = w & 31;
        if (t == 2/*text*/ || t == 3/*data*/) {
            *(p++) = w + 25; /* mark "estimated" */
            *(p++) = getw();
        } else {
            *(p++) = 0;
            *(p++) = 0;
            getw();
        }
    }
    close(fin);

    /* read in f-b definitions */
    fbbufp = p;
    ibufc = 0;
    fin = ofile(atmp2);
    while ((w = getw()) != 4/*EOT*/) {
        setbrk(p + 2);
        *(p++) = w + 25; /* "estimated" */
        *(p++) = getw();
    }
    close(fin);
    endtable = p;
    setbrk(p + 1);
    *(p++) = -1;

    /* set up input text file; initialize f-b table */
    passno = 1;
    setup();

    /* do pass 1 */
    ibufc = 0;
    fin = ofile(atmp1);
    assem();
    close(fin);

    if (outmod != 0777) aexit();
    savdot[*dotrel - 2] = *dot;

    /* prepare for pass 2 */
    passno = 2;
    setup();

    /* header */
    *txtmagic = 0407; /* br .+20 */
    *txtsiz = (savdot[0] + 1) & ~1;
    *datsiz = (savdot[1] + 1) & ~1;
    *bsssiz = (savdot[2] + 1) & ~1;

    savdot[0] = 0;
    savdot[1] = datbase = *txtsiz;
    savdot[2] = bssbase = *txtsiz + *datsiz;

    *txtseek  = 16;
    *datseek  = 16 + *txtsiz;
    *trelseek = 16 + *txtsiz + *datsiz;
    *drelseek = 16 + *txtsiz + *datsiz + *txtsiz;
    symseek   = 16 + *txtsiz + *datsiz + *txtsiz + *datsiz;

    for (p = usymtab; p < endtable; p =+ 2) {
        doreloc(p);
    }
    oset(txtp, 0);
    oset(relp, *trelseek);
    for (i = 0; i < 8; ++i) {
        putw(txtp, header[i]);
    }

    /* do pass 2 */
    ibufc = 0;
    fin = ofile(atmp1);
    assem();
    close(fin);

    /* polish off text and relocation */
    aflush(txtp);
    aflush(relp);

    /* append full symbol table */
    oset(txtp, symseek);
    p = usymtab;
    ibufc = 0;
    fin = ofile(atmp3);
    while ((w = getw()) != 4/*EOT*/) {
        putw(txtp, w);
        putw(txtp, getw());
        putw(txtp, getw());
        putw(txtp, getw());
        putw(txtp, *(p++));
        putw(txtp, *(p++));
        getw();
        getw();
    }
    close(fin);
    aflush(txtp);
    aexit();
}

int errflg;
char *aout;

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    chmod(aout, outmod);
    exit(errflg);
}

filerr(fn)
char *fn;
{
    if (!errflg) ++errflg;
    printf("%s?\n", fn);
    aexit();
}

int defund;

doreloc(sym)
int *sym;
{
    int t;
    if (sym->type == 0) sym->type = defund;
    t = sym->type & 31;
    if (t == 3) {
        sym->value =+ datbase;
    } else if (t == 4) {
        sym->value =+ bssbase;
    }
}

setbrk(p)
char *p;
{
    while (p > memend) {
        memend =+ 512;
        brk(memend);
    }
}

setup()
{
    int i;
    *dotrel = 2;
    *dot    = 0;
    *dotdot = 0; /* .. */
    brtabi  = 0;
    memset(curfb, 0, 20);
    memset(nxtfb, 0, 20);
    for (i = 0; i < 10; ++i) {
        fbadv(i);
    }
}

ofile(fn)
char *fn;
{
    int fd;
    if ((fd = open(fn, 0)) < 0) filerr(fn);
    return fd;
}
