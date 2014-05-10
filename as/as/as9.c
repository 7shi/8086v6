/* key to types

     0  undefined
     1  absolute
     2  text
     3  data
     4  bss
     5  flop freg,dst (movfo, = stcfd)
     6  branch
     7  jsr
     8  rts
     9  sys
    10  movf (=ldf,stf)
    11  double operand (mov)
    12  flop fsrc,freg (addf)
    13  single operand (clr)
    14  .byte
    15  string (.ascii, "<")
    16  .even
    17  .if
    18  .endif
    19  .globl
    20  register
    21  .text
    22  .data
    23  .bss
    24  mul,div, etc
    25  sob
    26  .comm
    27  estimated text
    28  estimated data
    29  jbr
    30  jeq, jne, etc
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

    "exit",      1, 0000001,
    "fork",      1, 0000002,
    "read",      1, 0000003,
    "write",     1, 0000004,
    "open",      1, 0000005,
    "close",     1, 0000006,
    "wait",      1, 0000007,
    "creat",     1, 0000010,
    "link",      1, 0000011,
    "unlink",    1, 0000012,
    "exec",      1, 0000013,
    "chdir",     1, 0000014,
    "time",      1, 0000015,
    "makdir",    1, 0000016,
    "chmod",     1, 0000017,
    "chown",     1, 0000020,
    "break",     1, 0000021,
    "stat",      1, 0000022,
    "seek",      1, 0000023,
    "tell",      1, 0000024,
    "mount",     1, 0000025,
    "umount",    1, 0000026,
    "setuid",    1, 0000027,
    "getuid",    1, 0000030,
    "stime",     1, 0000031,
    "fstat",     1, 0000034,
    "mdate",     1, 0000036,
    "stty",      1, 0000037,
    "gtty",      1, 0000040,
    "nice",      1, 0000042,
    "signal",    1, 0000060,

    /* double operand */

    "mov",      11, 0010000,
    "movb",     11, 0110000,
    "cmp",      11, 0020000,
    "cmpb",     11, 0120000,
    "bit",      11, 0030000,
    "bitb",     11, 0130000,
    "bic",      11, 0040000,
    "bicb",     11, 0140000,
    "bis",      11, 0050000,
    "bisb",     11, 0150000,
    "add",      11, 0060000,
    "sub",      11, 0160000,

    /* branch */

    "br",        6, 0000400,
    "bne",       6, 0001000,
    "beq",       6, 0001400,
    "bge",       6, 0002000,
    "blt",       6, 0002400,
    "bgt",       6, 0003000,
    "ble",       6, 0003400,
    "bpl",       6, 0100000,
    "bmi",       6, 0100400,
    "bhi",       6, 0101000,
    "blos",      6, 0101400,
    "bvc",       6, 0102000,
    "bvs",       6, 0102400,
    "bhis",      6, 0103000,
    "bec",       6, 0103000,
    "bcc",       6, 0103000,
    "blo",       6, 0103400,
    "bcs",       6, 0103400,
    "bes",       6, 0103400,

    /* jump/branch type */

    "jbr",      29, 0000400,
    "jne",      30, 0001000,
    "jeq",      30, 0001400,
    "jge",      30, 0002000,
    "jlt",      30, 0002400,
    "jgt",      30, 0003000,
    "jle",      30, 0003400,
    "jpl",      30, 0100000,
    "jmi",      30, 0100400,
    "jhi",      30, 0101000,
    "jlos",     30, 0101400,
    "jvc",      30, 0102000,
    "jvs",      30, 0102400,
    "jhis",     30, 0103000,
    "jec",      30, 0103000,
    "jcc",      30, 0103000,
    "jlo",      30, 0103400,
    "jcs",      30, 0103400,
    "jes",      30, 0103400,

    /* single operand */

    "clr",      13, 0005000,
    "clrb",     13, 0105000,
    "com",      13, 0005100,
    "comb",     13, 0105100,
    "inc",      13, 0005200,
    "incb",     13, 0105200,
    "dec",      13, 0005300,
    "decb",     13, 0105300,
    "neg",      13, 0005400,
    "negb",     13, 0105400,
    "adc",      13, 0005500,
    "adcb",     13, 0105500,
    "sbc",      13, 0005600,
    "sbcb",     13, 0105600,
    "tst",      13, 0005700,
    "tstb",     13, 0105700,
    "ror",      13, 0006000,
    "rorb",     13, 0106000,
    "rol",      13, 0006100,
    "rolb",     13, 0106100,
    "asr",      13, 0006200,
    "asrb",     13, 0106200,
    "asl",      13, 0006300,
    "aslb",     13, 0106300,
    "jmp",      13, 0000100,
    "swab",     13, 0000300,

    /* jsr */

    "jsr",       7, 0004000,

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

extern int hshsiz;
extern char *hshtab[];

/* シンボルテーブルを検索 */
symget(key, name)
char *name;
{
    int quot, idx;
    quot = ldiv(0, key, hshsiz); /* unsigned: key / hshsiz */
    idx  = lrem(0, key, hshsiz); /* unsigned: key % hshsiz */
    do {
        idx =- quot + 1;
        if (idx < 0) idx =+ hshsiz;
    } while (symcmp(idx, name));
    return idx;
}

extern char *usymtab;

/* シンボル名をチェック */
symcmp(idx, name)
{
    struct { char *cptr; };
    char *p;
    p = hshtab[idx];
    if (!p) return 0;
    if (!usymtab || p < usymtab) p = p->cptr;
    return strncmp(p, name, 8);
}

/* builtinシンボルをハッシュテーブルに追加 */
setup()
{
    int i, j, key, idx;
    char *name;

    for (i = 0; name = symtab[i]; i =+ 3) {
        /* 文字を加算してバイト反転しながらハッシュ値を算出 */
        for(key = 0, j = 0; j < 8 && name[j]; ++j) {
            key =+ name[j];
            key = (key << 8) + ((key >> 8) & 255);
        }
        idx = symget(key, name);
        hshtab[idx] = &symtab[i];
    }
}
