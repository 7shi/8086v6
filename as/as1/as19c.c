/* translated from as19.s */

/* key to types

	 0	undefined
	 1	absolute
	 2	text
	 3	data
	 4	bss
	 5	flop freg,dst (movfo, = stcfd)
	 6	branch
	 7	jsr
	 8	rts
	 9	sys
	10	movf (=ldf,stf)
	11	double operand (mov)
	12	flop fsrc,freg (addf)
	13	single operand (clr)
	14	.byte
	15	string (.ascii, "<")
	16	.even
	17	.if
	18	.endif
	19	.globl
	20	register
	21	.text
	22	.data
	23	.bss
	24	mul,div, etc
	25	sob
	26	.comm
	27	estimated text
	28	estimated data
	29	jbr
	30	jeq, jne, etc
*/

int symtab[] {

	/* special variables */

	".",         2, 0000000,
	"..",        1, 0000000,

	/* register */

	"r0",       20, 0000000,
	"r1",       20, 0000001,
	"r2",       20, 0000002,
	"r3",       20, 0000003,
	"r4",       20, 0000004,
	"r5",       20, 0000005,
	"sp",       20, 0000006,
	"pc",       20, 0000007,

	/* system calls */

	"exit",      1, 00000001,
	"fork",      1, 00000002,
	"read",      1, 00000003,
	"write",     1, 00000004,
	"open",      1, 00000005,
	"close",     1, 00000006,
	"wait",      1, 00000007,
	"creat",     1, 00000010,
	"link",      1, 00000011,
	"unlink",    1, 00000012,
	"exec",      1, 00000013,
	"chdir",     1, 00000014,
	"time",      1, 00000015,
	"makdir",    1, 00000016,
	"chmod",     1, 00000017,
	"chown",     1, 00000020,
	"break",     1, 00000021,
	"stat",      1, 00000022,
	"seek",      1, 00000023,
	"tell",      1, 00000024,
	"mount",     1, 00000025,
	"umount",    1, 00000026,
	"setuid",    1, 00000027,
	"getuid",    1, 00000030,
	"stime",     1, 00000031,
	"fstat",     1, 00000034,
	"mdate",     1, 00000036,
	"stty",      1, 00000037,
	"gtty",      1, 00000040,
	"nice",      1, 00000042,
	"signal",    1, 00000060,

	/* double operand */

	"mov",      11, 00010000,
	"movb",     11, 00110000,
	"cmp",      11, 00020000,
	"cmpb",     11, 00120000,
	"bit",      11, 00030000,
	"bitb",     11, 00130000,
	"bic",      11, 00040000,
	"bicb",     11, 00140000,
	"bis",      11, 00050000,
	"bisb",     11, 00150000,
	"add",      11, 00060000,
	"sub",      11, 00160000,

	/* branch */

	"br",        6, 00000400,
	"bne",       6, 00001000,
	"beq",       6, 00001400,
	"bge",       6, 00002000,
	"blt",       6, 00002400,
	"bgt",       6, 00003000,
	"ble",       6, 00003400,
	"bpl",       6, 00100000,
	"bmi",       6, 00100400,
	"bhi",       6, 00101000,
	"blos",      6, 00101400,
	"bvc",       6, 00102000,
	"bvs",       6, 00102400,
	"bhis",      6, 00103000,
	"bec",       6, 00103000,
	"bcc",       6, 00103000,
	"blo",       6, 00103400,
	"bcs",       6, 00103400,
	"bes",       6, 00103400,

	/* jump/branch type */

	"jbr",      29, 00000400,
	"jne",      30, 00001000,
	"jeq",      30, 00001400,
	"jge",      30, 00002000,
	"jlt",      30, 00002400,
	"jgt",      30, 00003000,
	"jle",      30, 00003400,
	"jpl",      30, 00100000,
	"jmi",      30, 00100400,
	"jhi",      30, 00101000,
	"jlos",     30, 00101400,
	"jvc",      30, 00102000,
	"jvs",      30, 00102400,
	"jhis",     30, 00103000,
	"jec",      30, 00103000,
	"jcc",      30, 00103000,
	"jlo",      30, 00103400,
	"jcs",      30, 00103400,
	"jes",      30, 00103400,

	/* single operand */

	"clr",      13, 00005000,
	"clrb",     13, 00105000,
	"com",      13, 00005100,
	"comb",     13, 00105100,
	"inc",      13, 00005200,
	"incb",     13, 00105200,
	"dec",      13, 00005300,
	"decb",     13, 00105300,
	"neg",      13, 00005400,
	"negb",     13, 00105400,
	"adc",      13, 00005500,
	"adcb",     13, 00105500,
	"sbc",      13, 00005600,
	"sbcb",     13, 00105600,
	"tst",      13, 00005700,
	"tstb",     13, 00105700,
	"ror",      13, 00006000,
	"rorb",     13, 00106000,
	"rol",      13, 00006100,
	"rolb",     13, 00106100,
	"asr",      13, 00006200,
	"asrb",     13, 00106200,
	"asl",      13, 00006300,
	"aslb",     13, 00106300,
	"jmp",      13, 00000100,
	"swab",     13, 00000300,

	/* jsr */

	"jsr",       7, 00004000,

	/* rts */

	"rts",       8, 0000200,

	/* simple operand */

	"sys",       9, 0104400,

	/* flag-setting */

	"clc",       1, 0000241,
	"clv",       1, 0000242,
	"clz",       1, 0000244,
	"cln",       1, 0000250,
	"sec",       1, 0000261,
	"sev",       1, 0000262,
	"sez",       1, 0000264,
	"sen",       1, 0000270,

	/* floating point ops */

	"cfcc",      1, 0170000,
	"setf",      1, 0170001,
	"setd",      1, 0170011,
	"seti",      1, 0170002,
	"setl",      1, 0170012,
	"clrf",     13, 0170400,
	"negf",     13, 0170700,
	"absf",     13, 0170600,
	"tstf",     13, 0170500,
	"movf",     10, 0172400,
	"movif",    12, 0177000,
	"movfi",     5, 0175400,
	"movof",    12, 0177400,
	"movfo",     5, 0176000,
	"addf",     12, 0172000,
	"subf",     12, 0173000,
	"mulf",     12, 0171000,
	"divf",     12, 0174400,
	"cmpf",     12, 0173400,
	"modf",     12, 0171400,
	"movie",    12, 0176400,
	"movei",     5, 0175000,
	"ldfps",    13, 0170100,
	"stfps",    13, 0170200,
	"fr0",      20, 0000000,
	"fr1",      20, 0000001,
	"fr2",      20, 0000002,
	"fr3",      20, 0000003,
	"fr4",      20, 0000004,
	"fr5",      20, 0000005,

	/* 11/45 operations */

	"als",      24, 0072000,
	"alsc",     24, 0073000,
	"mpy",      24, 0070000,
	"mul",      24, 0070000,
	"div",      24, 0071000,
	"ash",      24, 0072000,
	"ashc",     24, 0073000,
	"dvd",      24, 0071000,
	"xor",       7, 0074000,
	"sxt",      13, 0006700,
	"mark",      9, 0006400,
	"sob",      25, 0077000,

	/* specials */

	".byte",    14, 0000000,
	".even",    16, 0000000,
	".if",      17, 0000000,
	".endif",   18, 0000000,
	".globl",   19, 0000000,
	".text",    21, 0000000,
	".data",    22, 0000000,
	".bss",     23, 0000000,
	".comm",    26, 0000000,

	0
};

int *dotrel &symtab[1];
int *dot    &symtab[2];
int *dotdot &symtab[5];

char pof;
char fbfil;
char *unglob;
char nargs;
int curarg;
char atmp1[];
char atmp2[];

int aexit();

/*
 * void main (int argc, char* argv[])
 */
main(argc, argv) char *argv[];{
  if (signal(2/*SIGINT*/, 1) & 1 == 0) {
    signal(2, aexit);
  }

  nargs  = argc;
  curarg = argv;

  if (argv[1][0] == '-') {
    nargs--;
    curarg++;
  } else {
    unglob = 0;
  }

  setup();
  go();
}

int hshsiz;
int hshtab[];

/* シンボルテーブルを検索（独自関数） */
char **symget(key, name) char *name;{
  int quot, *idx;
  quot = ldiv(0, key, hshsiz);
  idx = hshtab + lrem(0, key, hshsiz);
  do {
    idx =- quot + 1;
    if(idx < hshtab) idx =+ hshsiz;
  } while (*idx && symcmp(*idx, name));
  return idx;
}

char *usymtab;

/* シンボル名をチェック（独自関数） */
symcmp(idx, name) int *idx;{
  if (idx < usymtab) idx = *idx;
  return strncmp(idx, name, 8);
}

/* builtinシンボルをハッシュテーブルに追加 */
setup(){
  char ch, **p;
  int key, i;

  for(p = symtab; *p; p =+ 3){
    /* バイト反転しながら文字を加算してハッシュを算出 */
    for(key = 0, i = 0; i < 8 && (ch = p[0][i]); ++i){
      key =+ ch;
      key = (key << 8) + ((key >> 8) & 255);
    }

    *symget(key, p[0]) = p;
  }
}
