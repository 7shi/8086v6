/* translated from as24.s */

struct Buf {
    int *next; /* next slot */
    int *max;  /* buf max */
    int addr;  /* seek addr */
    int data[256];
};

oset(buf, ad)
{
    buf->next = buf->data;
    buf->max  = &buf->data[256 - ((ad & 511) >> 1)];
    buf->addr = ad;
}

putw(buf, w)
{
    if (buf->next >= buf->max) {
        /* buf max */
        aflush(buf);
    }
    *(buf->next++) = w;
}

char faout;

aflush(buf)
{
    int len;
    len = (buf->next - buf->data) << 1;
    seek(faout, buf->addr, 0);
    write(faout, buf->data, len);
    oset(buf, buf->addr + len);
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
