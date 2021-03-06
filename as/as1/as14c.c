/* translated from as14.s */

extern char ch;

number(retval)
int *retval;
{
    int c, n10, n8;

    n10 = n8 = 0;
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
        *retval = n8;
        ch = c;
    }
    return 1;
}

extern char *hshtab[], symtab[], chartab[];
extern char *usymtab, *symend, *memend;

rname()
{
    char *sym, symbol[8];
    int c, i, key, tilde, idx;

    c = rch();
    /* symbol not for hash table */
    tilde = (c == '~');
    /* チルダ以外はバッファに戻す */
    if (!tilde) ch = c;

    /* シンボル名のバッファを初期化 */
    memset(symbol, 0, 8);

    /* 通常の文字が続く限り rch() でシンボル名を読み取り */
    for (key = 0, i = 0;; ++i) {
        c = rch();
        if (chartab[c] <= 0) break;
        key =+ c;
        key = (key << 8) | ((key >> 8) & 255);
        if (i < 8) symbol[i] = c;
    }
    ch = c;

    if (tilde) {
        idx = -1;
        sym = 0;
    } else {
        idx = symget(key, symbol);
        sym = hshtab[idx];
    }

    /* シンボルがなければ追加 */
    if (!sym) {
        sym = symend;
        symend =+ 12;
        /* メモリが足りなければ拡張 */
        if (symend > memend) {
            sbrk(512);
            memend =+ 512;
        }
        /* シンボルを初期化 */
        memcpy(sym, symbol, 8);
        memset(sym + 8, 0, 4);
        /* ハッシュテーブルからリンク */
        if (idx >= 0) hshtab[idx] = sym;
    }

    if (sym < usymtab) {
        /* builtin symbol */
        putw((sym - symtab) * 2 / 3 + 01000);
        return sym + 2;
    } else {
        /* user symbol */
        putw((sym - usymtab) / 3 + 04000);
        return sym + 8;
    }
}

extern char fin, inbuf[], fileflg, **curarg;
extern int line, nargs, inbfi, inbfcnt, ifflg;

/*
-- ch == 0の場合
最初の実行時はこの関数下部にある処理で
実行時引数となっているファイルを開き、descriptorを得る。
次にそのdescriptorからファイル内容を取得。
以降は関数が呼ばれる度に、ファイル内容を1文字づつ返す。

-- ch != 0の場合
chを0クリアし、関数実行時のchにあった値を返す
*/
rch() {
    int c, i;

    if (ch) {
        c = ch;
        ch = 0;
        return c;
    }

    for (;;) {
        while (inbfi < inbfcnt) {
            c = inbuf[inbfi++] & 127;
            if (c) return c;
        }

        /*
        read from file descriptor(=fin).
        descriptor going to get in later statements
        which opening the file that names were given by argv[](=curarg).
        */
        if (fin) {
            inbfcnt = read(fin, inbuf, 512);
            if (inbfcnt > 0) {
                inbfi = 0;
                continue;
            }
            close(fin);
            fin = 0;
        }

        if (ifflg != 0) {
            error("i"); /* if-endif nest */
            aexit();
        }

        if (--nargs <= 0) {
            return 4; /* EOT */
        }
        ++curarg;
        if (++fileflg < 0) {
            filerr(*curarg, "?\n");
            aexit();
        }

        fin = open(*curarg, 0);
        line = 1;

        putw(5);
        for (i = 0; c = (*curarg)[i]; ++i) {
            putw(c);
        }
        putw(-1);
    }
}
