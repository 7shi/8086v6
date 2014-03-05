/* translated from as14.s */

int  ch;
char *symbol;
int hshsiz 1553;
int hshtab[];
char symtab[];
char chartab[];
char *usymtab, *symend, *memend;

rname(r0)
int r0;
{
    int r3;
    char **r1p, *r4;
    int i, key, tilde;

    /* clearing symbol 8 chars */
    memset(symbol, 0, 8);

    key = 0;
    tilde = r0 == '~'; /* symbol not for hash table */

    /*
    retrieve source code by rch() while continuous normal characters
    */
    for (i = 0;; ++i) {
        r3 = chartab[r0 = rch()];
        if (r3 <= 0) break;
        key =+ r3;
        key = (key << 8) | ((key >> 8) & 255);
        if (i < 8) symbol[i] = r3;
    }

    ch = r0;
    
    if (tilde) {
        r1p = 0;
        r4 = 0;
    } else {
        r4 = *(r1p = symget(key, symbol));
    }

    /* 4: シンボルがなければ追加 */
    if (!r4) {
        r4 = symend;
        symend =+ 12;
        /* メモリが足りなければ拡張 */
        if (symend > memend) {
            sbrk(512);
            memend =+ 512;
        }
        /* 4: シンボルを初期化 */
        memcpy(r4, symbol, 8);
        memset(r4 + 8, 0, 4);
        if (r1p) *r1p = r4;
    }

    /* 1: */
    if (r4 >= usymtab) {
        /* user symbol */
        putw((r4 - usymtab) / 3 + 04000);
        return r4 + 8;
    }
    /* builtin symbol */
    putw((r4 - symtab) * 2 / 3 + 01000);
    return r4 + 2;
}

char inbuf[512];
char fin;
char fileflg;
char **curarg;
int nargs;
int inbfcnt;
char *inbfp;
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
    int r0;
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
        	if (readnum > 0) {
                inbfcnt = readnum;
                inbfp = inbuf;
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
            error("i");
            aexit();
        }

        filename = *++curarg;
        prevflg = fileflg;
        fileflg++;

        fin = open(filename, 0);
        if (fileflg < prevflg) {
            filerr(filename, "?\n");
            aexit();
        }

        line = 1;
        putw(5);

        n = 0;
        while (filename[n]) {
            putw(filename[n]);
            n++;
        }

        putw(-1);
    }

}
