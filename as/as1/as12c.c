/* translated from as12.s */

char errflg;
char **curarg;
int line;

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

int ifflg, obufi, outbuf[];
char pof;

putw(r4)
{
    if (!ifflg || r4 == '\n') {
        outbuf[obufi++] = r4;
        if (obufi >= 256) {
            write(pof, outbuf, 512);
            obufi = 0;
        }
    }
}
