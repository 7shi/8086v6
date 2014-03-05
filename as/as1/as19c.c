/* translated from as19.s */

/* key to types

	000	undefined
	001	absolute
	002	text
	003	data
	004	bss
	005	flop freg,dst (movfo, = stcfd)
	006	branch
	007	jsr
	010	rts
	011	sys
	012	movf (=ldf,stf)
	013	double operand (mov)
	014	flop fsrc,freg (addf)
	015	single operand (clr)
	016	.byte
	017	string (.ascii, "<")
	020	.even
	021	.if
	022	.endif
	023	.globl
	024	register
	025	.text
	026	.data
	027	.bss
	030	mul,div, etc
	031	sob
	032	.comm
	033	estimated text
	034	estimated data
	035	jbr
	036	jeq, jne, etc
*/

int symtab[] {

	/* special variables */

	".",		002, 0000000,
	"..",		001, 0000000,

	/* register */

	"r0",		024, 0000000,
	"r1",		024, 0000001,
	"r2",		024, 0000002,
	"r3",		024, 0000003,
	"r4",		024, 0000004,
	"r5",		024, 0000005,
	"sp",		024, 0000006,
	"pc",		024, 0000007,

	/* system calls */

	"exit",		001, 00000001,
	"fork",		001, 00000002,
	"read",		001, 00000003,
	"write",	001, 00000004,
	"open",		001, 00000005,
	"close",	001, 00000006,
	"wait",		001, 00000007,
	"creat",	001, 00000010,
	"link",		001, 00000011,
	"unlink",	001, 00000012,
	"exec",		001, 00000013,
	"chdir",	001, 00000014,
	"time",		001, 00000015,
	"makdir",	001, 00000016,
	"chmod",	001, 00000017,
	"chown",	001, 00000020,
	"break",	001, 00000021,
	"stat",		001, 00000022,
	"seek",		001, 00000023,
	"tell",		001, 00000024,
	"mount",	001, 00000025,
	"umount",	001, 00000026,
	"setuid",	001, 00000027,
	"getuid",	001, 00000030,
	"stime",	001, 00000031,
	"fstat",	001, 00000034,
	"mdate",	001, 00000036,
	"stty",		001, 00000037,
	"gtty",		001, 00000040,
	"nice",		001, 00000042,
	"signal",	001, 00000060,

	/* double operand */

	"mov",		013, 00010000,
	"movb",		013, 00110000,
	"cmp",		013, 00020000,
	"cmpb",		013, 00120000,
	"bit",		013, 00030000,
	"bitb",		013, 00130000,
	"bic",		013, 00040000,
	"bicb",		013, 00140000,
	"bis",		013, 00050000,
	"bisb",		013, 00150000,
	"add",		013, 00060000,
	"sub",		013, 00160000,

	/* branch */

	"br",		006, 00000400,
	"bne",		006, 00001000,
	"beq",		006, 00001400,
	"bge",		006, 00002000,
	"blt",		006, 00002400,
	"bgt",		006, 00003000,
	"ble",		006, 00003400,
	"bpl",		006, 00100000,
	"bmi",		006, 00100400,
	"bhi",		006, 00101000,
	"blos",		006, 00101400,
	"bvc",		006, 00102000,
	"bvs",		006, 00102400,
	"bhis",		006, 00103000,
	"bec",		006, 00103000,
	"bcc",		006, 00103000,
	"blo",		006, 00103400,
	"bcs",		006, 00103400,
	"bes",		006, 00103400,

	/* jump/branch type */

	"jbr",		035, 00000400,
	"jne",		036, 00001000,
	"jeq",		036, 00001400,
	"jge",		036, 00002000,
	"jlt",		036, 00002400,
	"jgt",		036, 00003000,
	"jle",		036, 00003400,
	"jpl",		036, 00100000,
	"jmi",		036, 00100400,
	"jhi",		036, 00101000,
	"jlos",		036, 00101400,
	"jvc",		036, 00102000,
	"jvs",		036, 00102400,
	"jhis",		036, 00103000,
	"jec",		036, 00103000,
	"jcc",		036, 00103000,
	"jlo",		036, 00103400,
	"jcs",		036, 00103400,
	"jes",		036, 00103400,

	/* single operand */

	"clr",		015, 00005000,
	"clrb",		015, 00105000,
	"com",		015, 00005100,
	"comb",		015, 00105100,
	"inc",		015, 00005200,
	"incb",		015, 00105200,
	"dec",		015, 00005300,
	"decb",		015, 00105300,
	"neg",		015, 00005400,
	"negb",		015, 00105400,
	"adc",		015, 00005500,
	"adcb",		015, 00105500,
	"sbc",		015, 00005600,
	"sbcb",		015, 00105600,
	"tst",		015, 00005700,
	"tstb",		015, 00105700,
	"ror",		015, 00006000,
	"rorb",		015, 00106000,
	"rol",		015, 00006100,
	"rolb",		015, 00106100,
	"asr",		015, 00006200,
	"asrb",		015, 00106200,
	"asl",		015, 00006300,
	"aslb",		015, 00106300,
	"jmp",		015, 00000100,
	"swab",		015, 00000300,

	/* jsr */

	"jsr",		007, 00004000,

	/* rts */

	"rts",		010, 0000200,

	/* simple operand */

	"sys",		011, 0104400,

	/* flag-setting */

	"clc",		001, 0000241,
	"clv",		001, 0000242,
	"clz",		001, 0000244,
	"cln",		001, 0000250,
	"sec",		001, 0000261,
	"sev",		001, 0000262,
	"sez",		001, 0000264,
	"sen",		001, 0000270,

	/* floating point ops */

	"cfcc",		001, 0170000,
	"setf",		001, 0170001,
	"setd",		001, 0170011,
	"seti",		001, 0170002,
	"setl",		001, 0170012,
	"clrf",		015, 0170400,
	"negf",		015, 0170700,
	"absf",		015, 0170600,
	"tstf",		015, 0170500,
	"movf",		012, 0172400,
	"movif",	014, 0177000,
	"movfi",	005, 0175400,
	"movof",	014, 0177400,
	"movfo",	005, 0176000,
	"addf",		014, 0172000,
	"subf",		014, 0173000,
	"mulf",		014, 0171000,
	"divf",		014, 0174400,
	"cmpf",		014, 0173400,
	"modf",		014, 0171400,
	"movie",	014, 0176400,
	"movei",	005, 0175000,
	"ldfps",	015, 0170100,
	"stfps",	015, 0170200,
	"fr0",		024, 0000000,
	"fr1",		024, 0000001,
	"fr2",		024, 0000002,
	"fr3",		024, 0000003,
	"fr4",		024, 0000004,
	"fr5",		024, 0000005,

	/* 11/45 operations */

	"als",		030, 0072000,
	"alsc",		030, 0073000,
	"mpy",		030, 0070000,
	"mul",		030, 0070000,
	"div",		030, 0071000,
	"ash",		030, 0072000,
	"ashc",		030, 0073000,
	"dvd",		030, 0071000,
	"xor",		007, 0074000,
	"sxt",		015, 0006700,
	"mark",		011, 0006400,
	"sob",		031, 0077000,

	/* specials */

	".byte",	016, 0000000,
	".even",	020, 0000000,
	".if",		021, 0000000,
	".endif",	022, 0000000,
	".globl",	023, 0000000,
	".text",	025, 0000000,
	".data",	026, 0000000,
	".bss",		027, 0000000,
	".comm",	032, 0000000,

	0,			000, 0000000
};

int *dotrel &symtab[1];
int *dot    &symtab[2];
int *dotdot &symtab[5];

/* for start() */
char pof;
char fbfil;
int unglob;
char nargs;
int curarg;
char atmp1[];
char atmp2[];

int aexit();

/*
 * void main (int argc, char* argv[])
 */
main(argc, argv) int argc; char *argv[];{
  int ret;

  ret = signal(2,1);
  if (ret & 1 == 0) {
    signal(2, aexit);
  }

  if (argv[1][0] == '-') {
    argv++;
    argc--;
  } else {
    unglob = 0;
  }

  nargs  = argc;
  curarg = argv;

  pof = fcreat(atmp1);
  fbfil = fcreat(atmp2);

  setup();
  go();
}

/* for setup() */
char *bsymtab, *memend, *symend;
char **srchsym();

/*
 * void setup(void);
 */
setup(){
  char ch, **p;
  int key, i;

  bsymtab = memend = symend = sbrk(0);

  for(p = symtab; *p; p =+ 3){
    /* バイト反転しながら文字を加算してハッシュを算出 */
    for(key = 0, i = 0; i < 8 && (ch = p[0][i]); ++i){
      key =+ ch;
      key = (key << 8) + ((key >> 8) & 0377);
    }

    *srchsym(key, p[0]) = addsym(p[0], p[1], p[2]);
  }
}
