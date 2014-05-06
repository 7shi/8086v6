/* translated from as21.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int outmod 0777;
int _savdot[], datbase, bssbase, ibufc, defund;
int *dotrel, *dot, *dotdot, brtabi, passno;
int header[], *txtmagic, *txtsiz, *datsiz, *bsssiz, *symsiz;
int *txtseek, *datseek, *trelseek, *drelseek, symseek;
char fin, *txtp[], *relp[], atmp1[], atmp2[], atmp3[];
char *usymtab, *endtable, *memend, faout, *aout;

/* set up sizes and origins */
go2()
{
    int t, *p, i, w;

    if ((faout = creat(aout, 0)) < 0) {
        _filerr(aout);
    }

    /* read in symbol table */
    p = usymtab;
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
    _setup();

    /* do pass 1 */
    ibufc = 0;
    fin = ofile(atmp1);
    _assem();
    close(fin);

    if (outmod != 0777) aexit();

    /* prepare for pass 2 */
    ++passno;
    _setup();

    /* header */
    *txtmagic = 0407; /* br .+20 */
    *txtsiz = (*txtsiz + 1) & ~1;
    *datsiz = (*datsiz + 1) & ~1;
    *bsssiz = (*bsssiz + 1) & ~1;

    _savdot[1] = datbase = *txtsiz;
    _savdot[2] = bssbase = *txtsiz + *datsiz;

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
        _putw(txtp, header[i]);
    }

    /* do pass 2 */
    ibufc = 0;
    fin = ofile(atmp1);
    _assem();
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
        _putw(txtp, w);
        _putw(txtp, getw());
        _putw(txtp, getw());
        _putw(txtp, getw());
        _putw(txtp, *(p++));
        _putw(txtp, *(p++));
        getw();
        getw();
    }
    close(fin);
    aflush(txtp);
    aexit();
}

int errflg;
char ch;

_filerr(fn)
char *fn;
{
    if (!errflg) ++errflg;
    printf("%s?\n", fn);
    aexit();
}

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

_setup()
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
    if ((fd = open(fn, 0)) < 0) _filerr(fn);
    return fd;
}
