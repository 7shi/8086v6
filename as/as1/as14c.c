/* translated from as14.s */

char ch;
char symbol;
char inbuf[512];
char fin;
char fileflg;
char **curarg;
int nargs;
int inbfcnt;
int *inbfp;
int ifflg;
int line;

int aexit();

/*
-- ch == 0の場合
最初の実行時はこの関数下部にある処理で
実行時引数となっているファイルを開き、descriptorを得る。
次にそのdescriptorからファイル内容を取得。
以降は関数が呼ばれる度に、ファイル内容を1文字づつ返す。

-- ch > 0の場合
chを0クリアし、関数実行時のchにあった値を返す
*/
rch() {
    int r0, r1, r4;
    int n, readnum;
    char *filename, prevflg;

    if (r0 = ch) {
        ch = 0;
        return r0;
    }

    for (;;) {
        while (--inbfcnt >= 0) {
            r0 = *inbfp & 0377;
            inbfp++;
            if (r0 =& 0177) {
                return r0;
            } else {
                continue;
            }
        }

        /*
        read from file descriptor(=fin).
        descriptor going to get in later statements
        which opening the file that names were given by argv[](=curarg).
        */
        if (fin) {
            readnum = read(fin, inbuf, 512);
            if (!(inbuf < 0 || readnum == 0)) {
                inbfcnt = readnum;
                inbfp = &inbuf;
                continue;
            }

            close(fin);
            fin = 0;
        }

        if (--nargs <= 0) {
            /*return "\e";*/
            return 4;
        }

        if (ifflg != 0) {
            error('i');
            aexit();
        }

        filename = curarg[1];
        curarg = &(curarg[1]);
        prevflg = fileflg;
        fileflg++;

        fin = open(filename, 0);
        if (fileflg < prevflg) {
            filerr(filename, "<?\n>");
            aexit();
        }

        line = 1;
        putw(5);

        n = 0;
        while ((*curarg)[n]) {
            putw((*curarg)[n]);
            n++;
        }

        putw(-1);
    }

}
