/* translated from as11.s */

struct Op { char type, num; int value; };
struct Op curfbr[];

int outmod, passno, errflg;
char atmp1[], atmp2[], atmp3[], faout, *aout;
char faout, fbfil, *txtp[];
char *usymtab, *symend, *memend;

int aexit();

go1()
{
    int fp, i;

    usymtab = symend = memend = sbrk(0);
    for (i = 0; i < 10; ++i) {
        curfbr[i].value = -1;
    }

    /* as2へ引き継ぐ一時ファイルを作成 */
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

    /* ファイルを閉じる */
    close(fp);
    close(fbfil);
    close(faout);

    /* エラーが発生していれば終了 */
    if (errflg) aexit(); 
}

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    if (passno) chmod(aout, outmod);
    exit(errflg);
}

filerr(fname, msg)
char *fname, *msg;
{
    printf("%s%s", fname, msg);
}

fcreat(atmp)
char *atmp;
{
    int ret, st[20];
    do {
        if(stat(atmp, st) < 0) {
            ret = creat(atmp, 0444);
            if(ret > 0) return ret;
        }
    } while (++atmp[9] <= 'z');
    filerr(atmp, "?\n");
    exit(1);
}
