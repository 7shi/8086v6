/* translated from as14.s */

char ch;
char *symbol;
int *symend;
int *hshsiz;
int *hshtab;
int *end;
char usymtab[36];
char symtab[];

rname(r0, r1, r2, r3)
int r0;
int r1;
char *r2;
char *r3;
{
    int r4, r5;
    int *r0p, *r1p, *r4p;
    int i, tmp1, tmp2;
    int loop_flag, jump_flag;
    int *sp;
    char stack[10];

    loop_flag = jump_flag = 0;
    sp = &stack[9];

    *sp = r1;
    *(--sp) = r2;
    *(--sp) = r3;

    
    r5 = 8;
    r2 = symbol+8;
    for (i = 0; i < 4; i++) {
        *r2 = 0;
        r2--;
    }
    *(--sp) = 0;
    *(--sp) = 0;
    
    /* see later */
    if (r0 == '~') {
        sp =+ 2;
        *sp =+ 1;
    }

    /*
    retrieve source code by rch() while continuous normal characters
    */
    for (;;) {
        r3 = rch();
        if (r3 <= 0) {
            break;
        } else {
            tmp1 = tmp2 = *sp + r3;
            tmp2 = tmp2 << 8;
            tmp1 = tmp1 >> 8;
            *sp = tmp1 | tmp2;

            if (--r5 >= 0) {
                *r2 = r3;
                r2++;
            }
        }
    }

    ch = r0;
    r1 = *(sp++);
    r0 = 0;
    
    if (*(sp++) != 0) {
        r4 = *symend;
    } else {
        r0 = r0 / hshsiz;
        r1 = r0 % hshsiz;
        r0 =* 2;
        r1 =* 2;
        r1p = hshtab + r1;

        for (;;) {
            r1p =- r0;
            if (r1p < hshtab) {
                r1 =+ 2*(*hshsiz);
            }

            r2 = symbol;
            r4p = *(--r1p);
            if (r4p != 0) {
                for (i = 0; i < 4; i++) {
                    if (*(r2++) != *(r4p++)) {
                        loop_flag = 1;
                        break;
                    }
                }
                if (loop_flag == 1) {
                    continue;
                } else {
                    jump_flag = 1;
                    break;
                }
            } else {
                break;
            }
        }

        if (jump_flag == 0) {
            /*3:*/
            r4 = *symend;
            *r1p = r4;
        }
    }

    /*4:*/
    if (jump_flag == 0) {
        r2 = symbol;
        *(--sp) = r4;
        r4 =+ 20;

        if (r4 > end) {
            end =+ 512;
        }
        /*4:*/
        r4p = *(sp++);
        for (i = 0; i < 4; i++) {
            *(r4p++) = *(r2++);
        }
        *(r4p++) = 0;
        *(r4p++) = 0;

        symend = *(r4p);
        r4p =- 4;
    }
       
    /* 1: */
    *(--sp) = r4p;
    r3 = r4p;
    r3 =- 8;
    if (r3 >= usymtab) {
        r3 =- usymtab;
        r2 = 0;
        r2 = 3 / r3;
        r3 = 3 % r3;
        r4p = r2;
        r4p =+ 4000;
    } else {
        r3 =- symtab;
        r2 = 0;
        r2 = 3 / r3;
        r3 = 3 % r3;
        r4p = r2;
        r4p =+ 1000;
    }

    putw(r4p);
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
