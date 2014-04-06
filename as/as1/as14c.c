/* translated from as14.s */

int hshtab[], hshsiz;
char symtab[], chartab[];
char ch, *usymtab, *symend, *memend;

number(retval)
int *retval;
{
    int c, n10, n8;

    n8 = n10 = 0;
    for (;;) {
        c = rch();
        if (c < '0' || '9' < c) break;
        
        c =- '0';
        n10 = (n10 * 10) + c;
        n8 = (n8 << 3) + c;
    }

    if (c == 'b' || c == 'f') {
        *retval = fbcheck(n10) + 'a';
        if (c == 'f') *retval =+ 10;
        return *retval;
    }

    if (c == '.') {
        *retval = n10;
    } else {
        ch = c;
        *retval = n8;
    }
    return 1;
}

rname(r0)
int r0;
{
    int r3;
    char **r1p, *r4, symbol[8];
    int i, key, tilde;

    /* symbol not for hash table */
    if (tilde = r0 == '~') {
        ch = 0;
    }

    /* シンボル名のバッファを初期化 */
    memset(symbol, 0, 8);

    /* 通常の文字が続く限り rch() でシンボル名を読み取り */
    for (key = 0, i = 0;; ++i) {
        r0 = rch();
        r3 = chartab[r0];
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
            r0 = *inbfp & 127;
            inbfp++;
            if (r0) {
                return r0;
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
            return 4; /* \e: EOT */
        }

        if (ifflg != 0) {
            error("i"); /* if-endif nest */
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
