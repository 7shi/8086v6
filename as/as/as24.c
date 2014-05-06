/* translated from as24.s */

struct Buf {
    int *next; /* next slot */
    int *max;  /* buf max */
    int addr;  /* seek addr */
    int data[256];
};

oset(this, ad)
struct Buf *this;
{
    this->next = this->data;
    this->max  = &this->data[256 - ((ad & 511) >> 1)];
    this->addr = ad;
}

_putw(this, w)
struct Buf *this;
{
    if (this->next >= this->max) {
        /* buf max */
        aflush(this);
    }
    *(this->next++) = w;
}

char faout;

aflush(this)
struct Buf *this;
{
    int len;
    len = (this->next - this->data) << 1;
    seek(faout, this->addr, 0); /* 仕様変更 */
    write(faout, this->data, len);
    oset(this, this->addr + len);
}

int savop;

_readop()
{
    int op;
    if (savop) {
        op = savop;
        savop = 0;
        return op;
    }
    return getw();
}

int inbuf[256], ibufi, ibufc;
char fin;

getw()
{
    int op, len;
    if (savop) {
        op = savop;
        savop = 0;
        return op;
    }
    if (ibufi >= ibufc) {
        len = read(fin, inbuf, 512);
        if (len < 0 || (ibufc = len >> 1) == 0) {
            return 4/*EOT*/;
        }
        ibufi = 0;
    }
    return inbuf[ibufi++];
}
