/* translated from as28.s */

char *aout "a.out";

int header[8];
int *txtmagic &header[0];
int *txtsiz   &header[1];
int *datsiz   &header[2];
int *bsssiz   &header[3];
int *symsiz   &header[4];
int *stksiz   &header[5];
int *exorig   &header[6];

int tseeks[3], rseeks[3], symseek;

int *txtseek &tseeks[0];
int *datseek &tseeks[1];

int *trelseek &rseeks[0];
int *drelseek &rseeks[1];

int brlen 1024;
char brtab[128]; /* bitmap: brlen / 8 */

int adrbuf[6];
int brtabi, brdelt, defund, datbase, bssbase;
int abufi, ibufi, ibufc, line, savop, numval, passno;

char argb[22], *txtp[259], *relp[259];
char fin, faout;
char *usymtab, *endtable, *xsymbol;

struct Op { char type, num; int value; };

/* 0: .. 9: */
struct Op curfbr[10], *curfb[10], *nxtfb[10], *fbbufp;
