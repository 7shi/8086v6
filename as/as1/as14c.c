/* translated from as14.s */

char ch;
char *symbol;
int *symend;
int hshsiz 1553;
char *hshtab;
char usymtab[36];
char symtab[];
char chartab[];

rname(r0)
int r0;
{
    int r1, r5;
    char *r2;
    char r3;
    int *r0p, *r1p, *r4;
    int i, tmp1, tmp2;
    int loop_flag, jump_flag;
    int stack[10];
    int *sp;

    loop_flag = jump_flag = 0;
    sp = &stack[10];

    r5 = 8;
    r2 = symbol+8;
	*(--r2) = 0;
	*(--r2) = 0;
	*(--r2) = 0;
	*(--r2) = 0;
    *(--sp) = 0;
    *(--sp) = 0;

    if (r0 == '~') {
        sp[1]++;
        ch = 0;
    }

    /*
    retrieve source code by rch() while continuous normal characters
    */
    for (;;) {
        r3 = chartab[r0 = rch()];
        if (r3 <= 0) {
            break;
        } else {
            tmp1 = tmp2 = *sp + r3;
            tmp2 = tmp2 << 8;
            tmp1 = (tmp1 >> 8) & 255;
            *sp = tmp1 | tmp2;
            debug8("line53: ", *sp);

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
        r4 = symend;
    } else {
        r0 = r0 / hshsiz;
        r1 = r0 % hshsiz;
        r0 =* 2;
        r1 =* 2;
        r1p = hshtab + r1;

        for (;;) {
            r1p =- r0;
            if (r1p < hshtab) {
                r1p =+ hshsiz;
            }

            r2 = symbol;
            r4 = *(--r1p);
            if (r4 != 0) {
                for (i = 0; i < 4; i++) {
                    if (*(r2++) != *(r4++)) {
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
            r4 = symend;
            *r1p = r4;
        }
    }

    /*4:*/
    if (jump_flag == 0) {
        debug8("line110:", r4);
        r2 = symbol;
        *(--sp) = r4;
        debug8("line112:", *sp);
        r4 =+ 20;

        /*4:*/
        r4 = *(sp++);
        for (i = 0; i < 4; i++) {
            *(r4++) = *(r2++);
        }
        *(r4++) = 0;
        *(r4++) = 0;

        symend = *(r4);
        r4 =- 4;
    }
       
    /* 1: */
    *(--sp) = r4;
    debug8("line129:", *sp);
    r3 = r4;
    r3 =- 8;
    if (r3 >= usymtab) {
        r3 =- usymtab;
        r2 = 0;
        r2 = 3 / r3;
        r3 = 3 % r3;
        r4 = r2;
        r4 =+ 4000;
    } else {
        r3 =- symtab;
        r2 = 0;
        r2 = 3 / r3;
        r3 = 3 % r3;
        r4 = r2;
        r4 =+ 1000;
    }

    putw(r4);

    return stack[9];
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
