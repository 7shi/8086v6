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
int rseeks[3];

int *tseekp tseeks;
int *rseekp rseeks;

int *txtseek &tseeks[0];
int *datseek &tseeks[1];

int *trelseek &rseeks[0];
int *drelseek &rseeks[1];
