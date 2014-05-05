/* translated from as21.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

int outmod 0777;
int _savdot[], datbase, bssbase, ibufc;
int *_dotrel, *_dot, *_dotdot, brtabi, passno;
int header[], *txtmagic, *txtsiz, *datsiz, *bsssiz, *symsiz;
int *txtseek, *datseek, *trelseek, *drelseek, symseek;
char fin, *txtp[], *relp[], *_atmp1, *_atmp2, *_atmp3;
char *usymtab, *endtable, *memend;

/* set up sizes and origins */
_go()
{
    int t, *p, i, w;

    /* read in symbol table */
    p = usymtab;
    fin = ofile(_atmp3);
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
    fin = ofile(_atmp2);
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
    fin = ofile(_atmp1);
    _assem();
    close(fin);

    /* prepare for pass 2 */
    if (outmod != 0777) _aexit();

    *_dot = 0;
    *_dotrel = 2;
    *_dotdot = 0; /* .. */
    brtabi = 0;
    ibufc = 0;
    _setup();
    ++passno;

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
    fin = ofile(_atmp1);
    _assem();
    close(fin);

    /* polish off text and relocation */
    aflush(txtp);
    aflush(relp);

    /* append full symbol table */
    ibufc = 0;
    oset(txtp, symseek);
    p = usymtab;
    fin = ofile(_atmp3);
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
    _aexit();
}

int errflg;
char *_atmp2, *_atmp3, *aout;

_aexit()
{
    unlink(_atmp1);
    unlink(_atmp2);
    unlink(_atmp3);
    chmod(aout, outmod);
    exit(errflg);
}

char ch;

_filerr(fn)
char *fn;
{
    if (!errflg) ++errflg;
    printf("%s?\n", fn);
    _aexit();
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

_setup()
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
    if ((fd = open(fn, 0)) < 0) _filerr(fn);
    return fd;
}
