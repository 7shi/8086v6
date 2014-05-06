/* translated from as11.s */

int outbuf[], outmod;
char atmp1[], atmp2[], atmp3[], faout, *aout;
char errflg, pof, fbfil;
char *usymtab, *symend, *memend;
char *unglob;

int aexit();

go1()
{
    int fp;

    usymtab = symend = memend = sbrk(0);

    /* as2へ引き継ぐ一時ファイルを作成 */
    pof   = fcreat(atmp1);
    fbfil = fcreat(atmp2);
    fp    = fcreat(atmp3);

    /* SIGINTが無視されていなければ、中断時に後片付け */
    if (signal(2/*SIGINT*/, 1) & 1 == 0) {
        signal(2, aexit);
    }

    assem();

    /* 出力バッファをフラッシュ */
    write(pof, outbuf, 512);

    /* シンボルテーブルをダンプ */
    write(fp, usymtab, symend - usymtab);

    /* ファイルを閉じる */
    close(fp);
    close(fbfil);
    close(pof);

    /* エラーが発生していれば終了 */
    if (errflg) aexit(); 
}

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
    if (faout) chmod(aout, outmod);
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
    int ret;
    do {
        if(stat(atmp, outbuf) < 0) {
            ret = creat(atmp, 0444);
            if(ret > 0) return ret;
        }
    } while (++atmp[9] <= 'z');
    filerr(atmp, "?\n");
    exit(1);
}
