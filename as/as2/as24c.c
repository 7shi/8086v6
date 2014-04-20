/* translated from as24.s */

oset(buf, r0)
{
    int *r1, next;
    r1 = buf;
    next = buf + 6;
    /* next slot */
    r1[0] = next + (r0 & 0777);
    /* buf max */
    r1[1] = next + 01000;
    /* seek addr */
    r1[2] = r0;
}

putw(buf, r0)
{
    int **r2;
    r2 = buf;
    if (r2[0] >= r2[1]) {
        /* buf max */
        aflush(r2);
    }
    *r2[0] = r0;
    ++r2[0];
}

char faout;

aflush(buf)
{
    int r1, *r2, next;
    r2 = buf;
    next = buf + 6;
    r1 = r2[2]; /* seek address */
    seek(faout, r1, 0);
    r2[2] = (r1 | 0777) + 1; /* new seek addr */
    r1 = next + (r1 & 0777); /* write address */
    write(faout, r1, r2[0] - r1);
    r2[0] = next; /* new next slot */
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
    int r0;
    if (savop) {
        r0 = savop;
        savop = 0;
        return r0;
    }
    if (--ibufc <= 0) {
        r0 = read(fin, inbuf, 512);
        if (r0 < 0 || (ibufc = r0 >> 1) == 0) {
            return 4/*EOT*/;
        }
        ibufp = inbuf;
    }
    return *(ibufp++);
}
