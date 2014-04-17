/* translated from as24.s */

oset(r0, r5)
{
    int *r1, next;
    r1 = r5;
    next = r5 + 6;
    /* next slot */
    r1[0] = next + (r0 & 0777);
    /* buf max */
    r1[1] = next + 01000;
    /* seek addr */
    r1[2] = r0;
}

putw(r0, r5)
{
    int **r2;
    r2 = r5;
    if (r2[0] >= r2[1]) {
        /* buf max */
        aflush(r2);
    }
    *r2[0] = r0;
    ++r2[0];
}

char fout;

aflush(r5)
{
    int r1, *r2, next;
    r2 = r5;
    next = r5 + 6;
    r1 = r2[2]; /* seek address */
    seek(fout, r1, 0);
    r2[2] = (r1 | 0777) + 1; /* new seek addr */
    r1 = next + (r1 & 0777); /* write address */
    write(fout, r1, r2[0] - r1);
    r2[0] = next; /* new next slot */
}

int savop;
char symtab[], *usymtab;

readop()
{
    int r4;
    if (savop) {
        r4 = savop;
        savop = 0;
        return r4;
    }
    r4 = getw();
    if (r4 >= 04000) {
        return usymtab + (r4 - 04000);
    } else if (r4 >= 01000) {
        return  symtab + (r4 - 01000);
    }
    return r4;
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
