/* translated from as24.s */

oset(buf, ad)
{
    int *p, next;
    p = buf;
    next = buf + 6;
    /* next slot */
    p[0] = next + (ad & 0777);
    /* buf max */
    p[1] = next + 01000;
    /* seek addr */
    p[2] = ad;
}

putw(buf, w)
int **buf;
{
    if (buf[0] >= buf[1]) {
        /* buf max */
        aflush(buf);
    }
    *buf[0] = w;
    ++buf[0];
}

char faout;

aflush(buf)
{
    int ad, *p, next;
    p = buf;
    next = buf + 6;
    ad = p[2]; /* seek address */
    seek(faout, ad, 0);
    p[2] = (ad | 0777) + 1; /* new seek addr */
    ad = next + (ad & 0777); /* write address */
    write(faout, ad, p[0] - ad);
    p[0] = next; /* new next slot */
}

int savop;
char symtab[], *usymtab;

readop()
{
    int op;
    if (savop) {
        op = savop;
        savop = 0;
        return op;
    }
    op = getw();
    if (op >= 04000) {
        return usymtab + (op - 04000);
    } else if (op >= 01000) {
        return  symtab + (op - 01000);
    }
    return op;
}

int inbuf[256], *ibufp, ibufc;
char fin;

getw()
{
    int op, len;
    if (savop) {
        op = savop;
        savop = 0;
        return op;
    }
    if (--ibufc <= 0) {
        len = read(fin, inbuf, 512);
        if (len < 0 || (ibufc = len >> 1) == 0) {
            return 4/*EOT*/;
        }
        ibufp = inbuf;
    }
    return *(ibufp++);
}
