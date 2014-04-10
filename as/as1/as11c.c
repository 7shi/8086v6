/* translated from as11.s */

int outbuf[];
char atmp1[], atmp2[], atmp3[];
char errflg, pof, fbfil;
char *usymtab, *symend, *memend;
char *unglob "-g";

go()
{
    int fp;

    usymtab = symend = memend = sbrk(0);

    /* as2へ引き継ぐ一時ファイルを作成 */
    pof   = fcreat(atmp1);
    fbfil = fcreat(atmp2);
    fp    = fcreat(atmp3);

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

    execl("/lib/as2", "/lib/as2", atmp1, atmp2, atmp3, unglob, 0);
    filerr("lib/as2", "?\n");
    exit(1);
}

aexit()
{
    unlink(atmp1);
    unlink(atmp2);
    unlink(atmp3);
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
