/* translated from as21.s */

int outmod 0777;
int savdot[], datbase, bssbase, ibufc, *fbbufp;
int *dotrel, *dot, *dotdot, brtabp, passno;
int header[], *txtsiz, *datsiz, *bsssiz, *symsiz;
int *datseek, *trelseek, *drelseek, symseek;
char symf, fbfil, fin, *txtp[], *relp[], *atmp1;
char *usymtab, *endtable, *memend;

/* set up sizes and origins */
go()
{
    int r0, r1, *r1p, r2, r3, w;

    /* read in symbol table */
    r1p = usymtab = memend = sbrk(0);
    setbrk(r1p);
    while (getw() != 4/*EOT*/) {
        *symsiz =+ 12; /* count symbols */
        getw();
        getw();
        getw();
        r0 = w = getw();
        r0 =& 037;
        if (r0 == 2/*text*/ || r0 == 3/*data*/) {
            w =+ 25; /* mark "estimated" */
            *(r1p++) = w;
            *(r1p++) = getw();
        } else {
            *(r1p++) = 0;
            *(r1p++) = 0;
            getw();
        }
        setbrk(r1p);
    }

    /* read in f-b definitions */
    fbbufp = r1p;
    fin = fbfil;
    ibufc = 0;
    while ((w = getw()) != 4/*EOT*/) {
        w =+ 25; /* "estimated" */
        *(r1p++) = w;
        *(r1p++) = getw();
        setbrk(r1p);
    }
    endtable = r1p;
    *(r1p++) = 0100000;

    /* set up input text file; initialize f-b table */
    setup();

    /* do pass 1 */
    assem();

    /* prepare for pass 2 */
    if (outmod != 0777) aexit();

    *dot = 0;
    *dotrel = 2;
    *dotdot = 0; /* .. */
    brtabp = 0;
    close(fin);
    fin = ofile(atmp1);
    ibufc = 0;
    setup();
    ++passno;
    ++*bsssiz;
    *bsssiz =& ~1;
    *txtsiz = r1 = (*txtsiz + 1) & ~1;
    *datsiz = r2 = (*datsiz + 1) & ~1;
    r3 = r1;
    datbase = r3; /* txtsiz */
    savdot[1] = r3;
    r3 =+ r2;
    bssbase = r3; /*txtsiz+datsiz */
    savdot[2] = r3;
    r3 =<< 1;
    r3 =+ 16;
    symseek = r3; /* 2*txtsiz+2*datsiz+16 */
    r3 =- r2;
    *drelseek = r3; /* 2*txtsiz+datsiz+16 */
    r3 =- r1;
    *trelseek = r3; /* txtsiz+datsiz+16 */
    r3 =- r2;
    *datseek = r3; /* txtsiz+16 */
    for (r1p = usymtab; r1p < endtable; r1p =+ 2) {
        doreloc(r1p);
    }
    oset(txtp, 0);
    oset(relp, *trelseek);
    for (r2 = 0; r2 < 8; ++r2) {
        putw(txtp, header[r2]);
    }
    assem();

    /* polish off text and relocation */
    aflush(txtp);
    aflush(relp);

    /* append full symbol table */
    seek(fin = symf, 0, 0);
    ibufc = 0;
    oset(txtp, symseek);
    r1p = usymtab;
    while ((w = getw()) != 4/*EOT*/) {
        putw(txtp, w);
        putw(txtp, getw());
        putw(txtp, getw());
        putw(txtp, getw());
        putw(txtp, *(r1p++));
        putw(txtp, *(r1p++));
        getw();
        getw();
    }
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

doreloc(r1)
int *r1;
{
    int r0;
    if (!(r0 = r1[0])) r1[0] =| defund;
    r0 =& 31;
    if (r0 == 3) {
        r1[1] =+ datbase;
    } else if (r0 == 4) {
        r1[1] =+ bssbase;
    }
}

setbrk(r1)
char *r1;
{
    if (r1 + 16 >= memend) {
        memend =+ 512;
        brk(memend);
    }
}

char txtfil;
int curfb[], nxtfb[];

setup()
{
    int i;
    memset(curfb, 0, 20);
    memset(nxtfb, 0, 20);
    fin = txtfil;
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
