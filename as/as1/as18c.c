/* translated from as18.s */

char chartab[256] {
    /*  0*/ -12, -12, -12, -12,  -2, -12, -12, -12,
    /*  8*/ -12, -18,  -2, -12, -12, -18, -12, -12,
    /* 16*/ -12, -12, -12, -12, -12, -12, -12, -12,
    /* 24*/ -12, -12, -12, -12, -12, -12, -12, -12,
    /* 32*/ -18, -16, -14, -12, -16, -16, -16, -10,
    /* 40*/ -16, -16, -16, -16, -16, -16,  46,  -6,
    /* 48*/  48,  49,  50,  51,  52,  53,  54,  55,
    /* 56*/  56,  57, -16,  -2,   0, -16, -12, -12,
    /* 64*/ -12,  65,  66,  67,  68,  69,  70,  71,
    /* 72*/  72,  73,  74,  75,  76,  77,  78,  79,
    /* 80*/  80,  81,  82,  83,  84,  85,  86,  87,
    /* 88*/  88,  89,  90, -16, -20, -16, -16,  95,
    /* 96*/ -12,  97,  98,  99, 100, 101, 102, 103,
    /*104*/ 104, 105, 106, 107, 108, 109, 110, 111,
    /*112*/ 112, 113, 114, 115, 116, 117, 118, 119,
    /*120*/ 120, 121, 122, -12, -22, -12, 126, -12
};
/* reversed chartab:
    -22 (fixor)  : |
    -20 (escp)   : \
    -18          : 9'\t', 13'\r', 32' '
    -16 (retread): !$%&()*+,-:=[]^
    -14 (dquote) : "
    -12 (garb)   : 0-3, 5-8, 11-12, 14-31, #>?@`{}, 127
    -10 (squote) : '
     -6 (skip)   : /
     -2 (retread): 4(EOT), 10'\n', 59';'
      0 (string) : <
        (ASCII)  : .0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
                   _abcdefghijklmnopqrstuvwxyz~
*/

char atmp1[] "/tmp/atm1a";
char atmp2[] "/tmp/atm2a";
char atmp3[] "/tmp/atm3a";

/* atmp1 */
char pof;
int outbuf[256], obufi;

/* atmp2 */
char fbfil;

/* input */
char fin, inbuf[512];
int inbfi, inbfcnt;

/* 0: .. 9: */
int curfbr[10];
int curfb[] {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

/* .text, .data, .bss */
int savdot[3];

int hshsiz 1553;
char *hshtab[1553];

int nargs;
char **curarg;

char fileflg, errflg, ch, *unglob;
int line, ifflg, savop, numval;

char *usymtab, *symend, *memend;
