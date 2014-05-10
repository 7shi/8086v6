/* translated from as12.s */

extern char errflg, **curarg;
extern int line;

error(e)
char *e;
{
    int i, ln;
    char buf[5];

    ++errflg;
    if (*curarg) {
        filerr(*curarg, "\n");
        *curarg = 0;
    }

    /* lineの値を10進数で文字列化する */
    ln = line;
    for (i = 0; i < 4; i++) {
        buf[3 - i] = '0' + (ln % 10);
        ln =/ 10;
    }
    buf[4] = 0;

    printf("%s %s\n", e, buf);
}

extern int ifflg, obufi, outbuf[];
extern char pof;

putw(w)
{
    if (!ifflg || w == '\n') {
        outbuf[obufi++] = w;
        if (obufi >= 256) {
            write(pof, outbuf, 512);
            obufi = 0;
        }
    }
}
