#include <unistd.h>
#include <stdint.h>

struct Buf {
    short *next; /* next slot */
    short *max;  /* buf max */
    int   addr;  /* seek addr */
    short data[256];
};

oset(this, ad)
struct Buf *this;
{
    this->next = this->data;
    this->max  = &this->data[256 - ((ad & 511) >> 1)];
    this->addr = ad;
}

extern int passno, ifflg;

aputw(this, w)
struct Buf *this;
{
    if (passno == 0 && ifflg && w != '\n') return;
    if (this->next >= this->max) {
        /* buf max */
        aflush(this);
    }
    *(this->next++) = w;
}

extern char faout;

aflush(this)
struct Buf *this;
{
    int len;
    len = (this->next - this->data) << 1;
    lseek(faout, this->addr, 0); /* 仕様変更 */
    write(faout, this->data, len);
    oset(this, this->addr + len);
}

extern intptr_t savop;
extern short inbuf[];
extern int ibufi, ibufc;
extern char fin;

agetw()
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
