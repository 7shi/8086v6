/* translated from as18.s */

char chartab[256] {
	-12, -12, -12, -12,  -2, -12, -12, -12,
	-12, -18,  -2, -12, -12, -18, -12, -12,
	-12, -12, -12, -12, -12, -12, -12, -12,
	-12, -12, -12, -12, -12, -12, -12, -12,
	-18, -16, -14, -12, -16, -16, -16, -10,
	-16, -16, -16, -16, -16, -16,  46,  -6,
	 48,  49,  50,  51,  52,  53,  54,  55,
	 56,  57, -16, -2,    0, -16, -12, -12,
	-12,  65,  66,  67,  68,  69,  70,  71,
	 72,  73,  74,  75,  76,  77,  78,  79,
	 80,  81,  82,  83,  84,  85,  86,  87,
	 88,  89,  90, -16, -20, -16, -16,  95,
	-12,  97,  98,  99, 100, 101, 102, 103,
	104, 105, 106, 107, 108, 109, 110, 111,
	112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, -12, -22, -12, 126, -12
};

char atmp1[] "/tmp/atm1a";
char atmp2[] "/tmp/atm2a";
char atmp3[] "/tmp/atm3a";

int curfb[] {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int outbuf[256];
int *obufp outbuf;
int hshsiz 1553;

char curfbr[10];
/* char savdot[6]; */
int hshtab[1553];
char pof, wordf, fin, fbfil, fileflg, errflg;
/* char ch; */
int line, inbfcnt;
/* int ifflg; */
int inbfp, nargs, curarg, opfound;
/* int savop, numval; */
struct { char op0, op1; int op2; } nxtfb;
