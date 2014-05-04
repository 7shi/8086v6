/* translated from as21.s */

struct Op { char type, num; int value; };
struct Op *curfb[10], *nxtfb[10], *fbbufp;

int outmod 0777;
int savdot[], datbase, bssbase, ibufc;
int *dotrel, *dot, *dotdot, brtabi, passno;
int header[], *txtsiz, *datsiz, *bsssiz, *symsiz;
int *datseek, *trelseek, *drelseek, symseek;
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
        setbrk(p + 6);
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
    setup();

    /* do pass 1 */
    fin = ofile(atmp1);
    assem();
    close(fin);

    /* prepare for pass 2 */
    if (outmod != 0777) aexit();

    *dot = 0;
    *dotrel = 2;
    *dotdot = 0; /* .. */
    brtabi = 0;
    ibufc = 0;
    setup();
    ++passno;
    ++*bsssiz;
    *bsssiz =& ~1;
    *txtsiz = (*txtsiz + 1) & ~1;
    *datsiz = (*datsiz + 1) & ~1;
    savdot[1] = datbase = *txtsiz;
    savdot[2] = bssbase = *txtsiz + *datsiz;
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
    fin = ofile(atmp1);
    assem();
    close(fin);

    /* polish off text and relocation */
    aflush(txtp);
    aflush(relp);

    /* append full symbol table */
    ibufc = 0;
    oset(txtp, symseek);
    p = usymtab;
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
char *atmp2, *atmp3, *aout;

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    chmod(aout, outmod);
    exit(errflg);
}

char ch;

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
    memset(curfb, 0, 20);
    memset(nxtfb, 0, 20);
    ibufc = 0;
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
