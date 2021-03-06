#include <string.h>
#include <stdint.h>

extern intptr_t savop;
extern int numval, passno;
extern char ch, chartab[], *txtp[], symtab[], *usymtab;

intptr_t rname();

union Op { intptr_t op; struct Sym *sym; };

union Op
readop() {
    intptr_t ret;
    int c, num, type;
    if (savop) {
        ret = savop;
        savop = 0;
        return (union Op)ret;
    } else if (passno) {
        ret = agetw();
        if (ret >= 04000) {
            ret = (intptr_t)(usymtab + (ret - 04000));
        } else if (ret >= 01000) {
            ret = (intptr_t)( symtab + (ret - 01000) * 3 + 8);
        } else if (ret == 1) {
            numval = agetw();
        }
        return (union Op)ret;
    }
    for (;;) {
        c = rch(); /* 0-127 */
        type = chartab[c];
        if (type == -12 /* garb: #>?@`{} etc */) {
            error("g");
        } else if (type != -18 /* '\t', '\r', ' ' */) {
            break;
        }
    }
    switch (type) {
    case -22: /* fixor: | */
        ret = 31;
        break;
    case -20: /* escp: \ */
        switch (rch()) {
        case '/': ret = '/'; break; /* \/ avoid comment */
        case '<': ret = 29; break;
        case '>': ret = 30; break;
        case '%': ret = 31; break;
        default : ret = '\\'; break;
        }
        break;
    case -16: /* retread: !$%&()*+,-:=[]^ */
    case  -2: /* retread: 4(EOT), 10'\n', 59';' */
        ret = c;
        break;
    case -14: /* dquote: " */
        c = rsch(0);
        num = (rsch(0) << 8) | c;
        ret = 1;
        break;
    case -10: /* squote: ' */
        num = rsch(0);
        ret = 1;
        break;
    case -6: /* skip: / (comment) */
        do {
            ret = rch();
        } while (ret != 4/*EOT*/ && ret != '\n');
        break;
    case 0: /* string: < */
        aputw(txtp, '<');
        for (numval = 0; (c = rsch(1)) >= 0; ++numval) {
            aputw(txtp, c | 256);
        }
        aputw(txtp, -1);
        return (union Op)(intptr_t)'<';
    default: /* ASCII */
        ch = c;
        if ('0' <= c && c <= '9') {
            ret = number(&num);
            break;
        }
        return (union Op)rname();
    }
    aputw(txtp, ret);
    if (ret == 1) {
        /* default(数字), squote, dquote */
        aputw(txtp, numval = num);
    }
    return (union Op)ret;
}

rsch(isstr)
{
    int c;
    c = rch();
    if (c == 4/*EOT*/ || c == '\n') {
        error("<");
        aexit();
    } else if (c == '\\') {
        switch (c = rch()) {
        case 'n': return 10;
        case 't': return  9;
        case 'e': return  4;
        case '0': return  0;
        case 'r': return 13;
        case 'a': return  6;
        case 'p': return 27;
        }
    } else if (isstr && c == '>') {
        return -1;
    }
    return c;
}

number(retval)
int *retval;
{
    int c, n10, n8;

    n10 = n8 = 0;
    for (;;) {
        c = rch();
        if (c < '0' || '9' < c) break;
        c -= '0';
        n10 = (n10 * 10) + c;
        n8 = (n8 << 3) + c;
    }

    if (c == 'b' || c == 'f') {
        *retval = fbcheck(n10) + 'a';
        if (c == 'f') *retval += 10;
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

extern char *hshtab[], *symend, *memend;

intptr_t
rname()
{
    char *sym, symbol[8];
    int c, i, tilde, idx;
    short key;

    c = rch();
    /* symbol not for hash table */
    tilde = (c == '~');
    /* チルダ以外はバッファに戻す */
    if (!tilde) ch = c;

    /* シンボル名のバッファを初期化 */
    memset(symbol, 0, sizeof(symbol));

    /* 通常の文字が続く限り rch() でシンボル名を読み取り */
    for (key = 0, i = 0;; ++i) {
        c = rch();
        if (chartab[c] <= 0) break;
        key += c;
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
        symend += 12;
        /* メモリが足りなければ拡張 */
        setbrk(symend);
        /* シンボルを初期化 */
        memcpy(sym, symbol, 8);
        memset(sym + 8, 0, 4);
        /* ハッシュテーブルからリンク */
        if (idx >= 0) hshtab[idx] = sym;
    }

    if (sym < usymtab) {
        /* builtin symbol */
        aputw(txtp, (sym - symtab) / 3 + 01000);
    } else {
        /* user symbol */
        aputw(txtp, (sym - usymtab) / 3 + 04000);
    }
    return (intptr_t)(sym + 8);
}

extern char fin, inbuf[], fileflg, **curarg;
extern int line, nargs, inbfi, inbfcnt, ifflg;

/*
最初の実行時はこの関数下部にある処理で
実行時引数となっているファイルを開き、descriptorを得る。
次にそのdescriptorからファイル内容を取得。
以降は関数が呼ばれる度に、ファイル内容を1文字づつ返す。
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
            filerr(*curarg, "?");
            aexit();
        }

        fin = open(*curarg, 0);
        line = 1;

        aputw(txtp, 5);
        for (i = 0; c = (*curarg)[i]; ++i) {
            aputw(txtp, c);
        }
        aputw(txtp, -1);
    }
}
