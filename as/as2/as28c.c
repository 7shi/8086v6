/* translated from as28.s */

char *aout "a.out";
char *atmp1, *astmp2, *atmp3;

int header[8] { 00407 /* br .+20 */ };
int *txtmagic &header[0];
int *txtsiz   &header[1];
int *datsiz   &header[2];
int *bsssiz   &header[3];
int *symsiz   &header[4];
int *stksiz   &header[5];
int *exorig   &header[6];

int tseeks[3] { 16 };
int rseeks[3], symseek;

int *tseekp tseeks;
int *rseekp rseeks;

int *txtseek &tseeks[0];
int *datseek &tseeks[1];

int *trelseek &rseeks[0];
int *drelseek &rseeks[1];

int brlen 1024;
char brtab[128]; /* bitmap: brlen / 8 */

int savdot[3], adrbuf[6], curfb[10], nxtfb[10];
int brtabi, brdelt, fbbufp, defund, datbase, bssbase;
int ibufc, *ibufp, line, savop, numval, passno;

char argb[22], *txtp[259], *relp[259];
char fin, faout, wordf, ch;
char *usymtab, *endtable, *xsymbol;

int curfb[10], nxtfb[10];
