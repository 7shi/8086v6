/* translated from as21.s */

struct Op { char type, num; int value; };
struct Op curfbr[], *curfb[], *nxtfb[], *fbbufp;

int outmod 0777;
int savdot[], datbase, bssbase, ibufc, defund;
int *dotrel, *dot, *dotdot, brtabi, passno, errflg;
int header[], *txtmagic, *txtsiz, *datsiz, *bsssiz, *symsiz;
int *txtseek, *datseek, *trelseek, *drelseek, symseek;
char fbfil, fin, *txtp[], *relp[], atmp1[], atmp2[], atmp3[];
char *usymtab, *symend, *endtable, *memend, faout, *aout;

aexit();

/* pass 0 (as1) */
go0()
{
    int fp, i;

    usymtab = symend = memend = sbrk(0);
    for (i = 0; i < 10; ++i) {
        curfbr[i].value = -1;
    }

    faout = fcreat(atmp1);
    fbfil = fcreat(atmp2);
    fp    = fcreat(atmp3);

    /* SIGINTが無視されていなければ、中断時に後片付け */
    if (signal(2/*SIGINT*/, 1) & 1 == 0) {
        signal(2, aexit);
    }

    oset(txtp, 0);
    assem();
    aflush(txtp);

    /* シンボルテーブルをダンプ */
    write(fp, usymtab, symend - usymtab);

    close(fp);
    close(fbfil);
    close(faout);

    if (errflg) aexit(); 
}

/* pass 1 (as2) */
go1()
{
    int t, *p, w;

    if ((faout = creat(aout, 0)) < 0) {
        _filerr(aout);
    }
    passno = 1;

    /* read in symbol table */
    p = usymtab;
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
    _setup();

    /* do pass 1 */
    memset(savdot, 0, 6);
    ibufc = 0;
    fin = ofile(atmp1);
    _assem();
    close(fin);
    savdot[*dotrel - 2] = *dot;

    if (errflg) aexit(); 
}

/* pass 2 (as2) */
go2() {
    int i, *p, w;

    /* prepare for pass 2 */
    passno = 2;
    _setup();

    /* header */
    *txtmagic = 0407; /* br .+20 */
    *txtsiz = (savdot[0] + 1) & ~1;
    *datsiz = (savdot[1] + 1) & ~1;
    *bsssiz = (savdot[2] + 1) & ~1;

    savdot[0] = 0;
    savdot[1] = datbase = *txtsiz;
    savdot[2] = bssbase = *txtsiz + *datsiz;

    /* set up sizes and origins */
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
