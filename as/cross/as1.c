#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

struct Sym { char type, num; short value; };
extern struct Sym curfbr[], *curfb[], *nxtfb[], *fbbufp;

extern int outmod, savdot[], datbase, bssbase, ibufc, defund, nargs;
extern int *dotrel, *dot, *dotdot, brtabi, passno, errflg;
extern int header[], *txtmagic, *txtsiz, *datsiz, *bsssiz, *symsiz;
extern int *txtseek, *datseek, *trelseek, *drelseek, symseek;
extern char fbfil, faout, fin, *txtp[], *relp[], atmp1[], atmp2[], atmp3[];
extern char *usymtab, *symend, *endtable, *memend, *aout, **curarg;

main(argc, argv)
char *argv[];
{
    if (argc < 2) {
        printf("usage: as [-] source1 [source2 ...]\n");
        exit(1);
    }

    nargs  = argc;
    curarg = argv;

    if (argv[1][0] == '-') {
        /* globalize all undefineds */
        defund = 040;
        nargs--;
        curarg++;
    }

    setup();
    go0();
    go1();
    go2();
    aexit();
}

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    if (passno) chmod(aout, outmod);
    exit(errflg);
}

/* pass 0 (as1) */
go0()
{
    int i, symf;

    usymtab = symend = malloc(0x10000);
    memend = usymtab + 0x10000;

    for (i = 0; i < 10; ++i) {
        curfbr[i].value = -1;
    }

    faout = fcreat(atmp1);
    fbfil = fcreat(atmp2);
    symf  = fcreat(atmp3);

    /* SIGINTが無視されていなければ、中断時に後片付け */
    if (signal(2/*SIGINT*/, 1) & 1 == 0) {
        signal(2, aexit);
    }

    oset(txtp, 0);
    assem();
    aflush(txtp);

    /* シンボルテーブルをダンプ */
    write(symf, usymtab, symend - usymtab);

    close(symf);
    close(fbfil);
    close(faout);

    if (errflg) aexit(); 
}

/* pass 1 (as2) */
go1()
{
    int t;
    short *p, w;

    passno = 1;
    if ((faout = open(aout, O_CREAT | O_BINARY | O_WRONLY, S_IWRITE)) < 0) {
        filerr(aout, "?");
    }

    /* read in symbol table */
    p = (short *)usymtab;
    fin = ofile(atmp3);
    while (agetw() != 4/*EOT*/) {
        setbrk(p + 2);
        *symsiz += 12; /* count symbols */
        agetw();
        agetw();
        agetw();
        w = agetw();
        t = w & 31;
        if (t == 2/*text*/ || t == 3/*data*/) {
            *(p++) = w + 25; /* mark "estimated" */
            *(p++) = agetw();
        } else {
            *(p++) = 0;
            *(p++) = 0;
            agetw();
        }
    }
    close(fin);

    /* read in f-b definitions */
    fbbufp = (struct Sym *)p;
    ibufc = 0;
    fin = ofile(atmp2);
    while ((w = agetw()) != 4/*EOT*/) {
        setbrk(p + 2);
        *(p++) = w + 25; /* "estimated" */
        *(p++) = agetw();
    }
    close(fin);
    endtable = (char *)p;
    setbrk(p + 1);
    *(p++) = -1;

    /* initialize f-b table */
    init();

    /* do pass 1 */
    memset(savdot, 0, 6);
    ibufc = 0;
    fin = ofile(atmp1);
    assem();
    close(fin);
    savdot[*dotrel - 2] = *dot;

    if (errflg) aexit(); 
}

/* pass 2 (as2) */
go2() {
    int i;
    short *p, w;

    /* prepare for pass 2 */
    passno = 2;

    /* initialize f-b table */
    init();

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

    for (p = (short *)usymtab; p < (short *)endtable; p += 2) {
        doreloc(p);
    }
    oset(txtp, 0);
    oset(relp, *trelseek);
    for (i = 0; i < 8; ++i) {
        aputw(txtp, header[i]);
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
    p = (short *)usymtab;
    ibufc = 0;
    fin = ofile(atmp3);
    while ((w = agetw()) != 4/*EOT*/) {
        aputw(txtp, w);
        aputw(txtp, agetw());
        aputw(txtp, agetw());
        aputw(txtp, agetw());
        aputw(txtp, *(p++));
        aputw(txtp, *(p++));
        agetw();
        agetw();
    }
    close(fin);
    aflush(txtp);
}

init()
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

doreloc(sym)
struct Sym *sym;
{
    int t;
    if (sym->type == 0) sym->type = defund;
    t = sym->type & 31;
    if (t == 3) {
        sym->value += datbase;
    } else if (t == 4) {
        sym->value += bssbase;
    }
}

setbrk(p)
char *p;
{
    if (p > memend) {
        printf("Out of memory.\n");
        exit(1);
    }
}

filerr(fname, msg)
char *fname, *msg;
{
    if (!errflg) ++errflg;
    printf("%s%s\n", fname, msg);
    if (passno) aexit();
}

ofile(fn)
char *fn;
{
    int fd;
    if ((fd = open(fn, O_BINARY | O_RDWR)) < 0) {
        filerr(fn, "?");
    }
    return fd;
}

fcreat(atmp)
char *atmp;
{
    int ret = mkstemp(atmp);
    if (ret != -1) return ret;
    filerr(atmp, "?");
    exit(1);
}
