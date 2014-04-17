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
    /* read in symbol table */
    int r0, r1, *r1p, r2, r3, r4;
    r1p = usymtab = memend = sbrk(0);
    setbrk(r1p);
    while (getw() != 4/*EOT*/) {
        *symsiz =+ 12; /* count symbols */
        getw();
        getw();
        getw();
        r0 = r4 = getw();
        r0 =& 037;
        if (r0 == 2/*text*/ || r0 == 3/*data*/) {
            r4 =+ 25; /* mark "estimated" */
            *(r1p++) = r4;
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
    while ((r4 = getw()) != 4/*EOT*/) {
        r4 =+ 25; /* "estimated" */
        *(r1p++) = r4;
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
    r1 = (*txtsiz + 1) & ~1;
    *txtsiz = r1;
    r2 = (*datsiz + 1) & ~1;
    *datsiz = r2;
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
    oset(0, txtp);
    oset(*trelseek, relp);
    for (r2 = 0; r2 < 8; ++r2) {
        putw(header[r2], txtp);
    }
    assem();

    /* polish off text and relocation */
    flush(txtp);
    flush(relp);

    /* append full symbol table */
    seek(fin = symf, 0, 0);
    ibufc = 0;
    oset(symseek, txtp);
    r1p = usymtab;
    while ((r4 = getw()) != 4/*EOT*/) {
        putw(r4, txtp);
        putw(getw(), txtp);
        putw(getw(), txtp);
        putw(getw(), txtp);
        putw(*(r1p++), txtp);
        putw(*(r1p++), txtp);
        getw();
        getw();
    }
    flush(txtp);
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

filerr(r5)
char *r5;
{
    if (!errflg) ++errflg;
    write(1, r5, strlen(r5));
    write(1, "?\n", 2);
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

ofile(r5)
char *r5;
{
    int r0;
    if ((r0 = open(r5, 0)) < 0) filerr(r5);
    return r0;
}
