/* translated from as29.s */

int symtab[] {

    /* special variables */

    02, 0000000, /* .  */
    01, 0000000, /* .. */

    /* register */

    20, 0000000, /* r0 */
    20, 0000001, /* r1 */
    20, 0000002, /* r2 */
    20, 0000003, /* r3 */
    20, 0000004, /* r4 */
    20, 0000005, /* r5 */
    20, 0000006, /* sp */
    20, 0000007, /* pc */

    /* system calls */

    01, 0000001, /* exit   */
    01, 0000002, /* fork   */
    01, 0000003, /* read   */
    01, 0000004, /* write  */
    01, 0000005, /* open   */
    01, 0000006, /* close  */
    01, 0000007, /* wait   */
    01, 0000010, /* creat  */
    01, 0000011, /* link   */
    01, 0000012, /* unlink */
    01, 0000013, /* exec   */
    01, 0000014, /* chdir  */
    01, 0000015, /* time   */
    01, 0000016, /* makdir */
    01, 0000017, /* chmod  */
    01, 0000020, /* chown  */
    01, 0000021, /* break  */
    01, 0000022, /* stat   */
    01, 0000023, /* seek   */
    01, 0000024, /* tell   */
    01, 0000025, /* mount  */
    01, 0000026, /* umount */
    01, 0000027, /* setuid */
    01, 0000030, /* getuid */
    01, 0000031, /* stime  */
    01, 0000034, /* fstat  */
    01, 0000036, /* mdate  */
    01, 0000037, /* stty   */
    01, 0000040, /* gtty   */
    01, 0000042, /* nice   */
    01, 0000060, /* signal */

    /* double operand */

    11, 0010000, /* mov  */
    11, 0110000, /* movb */
    11, 0020000, /* cmp  */
    11, 0120000, /* cmpb */
    11, 0030000, /* bit  */
    11, 0130000, /* bitb */
    11, 0040000, /* bic  */
    11, 0140000, /* bicb */
    11, 0050000, /* bis  */
    11, 0150000, /* bisb */
    11, 0060000, /* add  */
    11, 0160000, /* sub  */

    /* branch */

    06, 0000400, /* br   */
    06, 0001000, /* bne  */
    06, 0001400, /* beq  */
    06, 0002000, /* bge  */
    06, 0002400, /* blt  */
    06, 0003000, /* bgt  */
    06, 0003400, /* ble  */
    06, 0100000, /* bpl  */
    06, 0100400, /* bmi  */
    06, 0101000, /* bhi  */
    06, 0101400, /* blos */
    06, 0102000, /* bvc  */
    06, 0102400, /* bvs  */
    06, 0103000, /* bhis */
    06, 0103000, /* bec  */
    06, 0103000, /* bcc  */
    06, 0103400, /* blo  */
    06, 0103400, /* bcs  */
    06, 0103400, /* bes  */

    /* jump/ branch type */

    29, 0000400, /* jbr  */
    30, 0001000, /* jne  */
    30, 0001400, /* jeq  */
    30, 0002000, /* jge  */
    30, 0002400, /* jlt  */
    30, 0003000, /* jgt  */
    30, 0003400, /* jle  */
    30, 0100000, /* jpl  */
    30, 0100400, /* jmi  */
    30, 0101000, /* jhi  */
    30, 0101400, /* jlos */
    30, 0102000, /* jvc  */
    30, 0102400, /* jvs  */
    30, 0103000, /* jhis */
    30, 0103000, /* jec  */
    30, 0103000, /* jcc  */
    30, 0103400, /* jlo  */
    30, 0103400, /* jcs  */
    30, 0103400, /* jes  */

    /* single operand */

    13, 0005000, /* clr  */
    13, 0105000, /* clrb */
    13, 0005100, /* com  */
    13, 0105100, /* comb */
    13, 0005200, /* inc  */
    13, 0105200, /* incb */
    13, 0005300, /* dec  */
    13, 0105300, /* decb */
    13, 0005400, /* neg  */
    13, 0105400, /* negb */
    13, 0005500, /* adc  */
    13, 0105500, /* adcb */
    13, 0005600, /* sbc  */
    13, 0105600, /* sbcb */
    13, 0005700, /* tst  */
    13, 0105700, /* tstb */
    13, 0006000, /* ror  */
    13, 0106000, /* rorb */
    13, 0006100, /* rol  */
    13, 0106100, /* rolb */
    13, 0006200, /* asr  */
    13, 0106200, /* asrb */
    13, 0006300, /* asl  */
    13, 0106300, /* aslb */
    13, 0000100, /* jmp  */
    13, 0000300, /* swab */

    /* jsr */

    07, 0004000, /* jsr */

    /* rts */

    08, 0000200, /* rts */

    /* simple operand */

    09, 0104400, /* sys */

    /* flag-setting */

    01, 0000241, /* clc */
    01, 0000242, /* clv */
    01, 0000244, /* clz */
    01, 0000250, /* cln */
    01, 0000261, /* sec */
    01, 0000262, /* sev */
    01, 0000264, /* sez */
    01, 0000270, /* sen */

    /* floating point ops */

    01, 0170000, /* cfcc  */
    01, 0170001, /* setf  */
    01, 0170011, /* setd  */
    01, 0170002, /* seti  */
    01, 0170012, /* setl  */
    13, 0170400, /* clrf  */
    13, 0170700, /* negf  */
    13, 0170600, /* absf  */
    13, 0170500, /* tstf  */
    10, 0172400, /* movf  */
    12, 0177000, /* movif */
    05, 0175400, /* movfi */
    12, 0177400, /* movof */
    05, 0176000, /* movfo */
    12, 0172000, /* addf  */
    12, 0173000, /* subf  */
    12, 0171000, /* mulf  */
    12, 0174400, /* divf  */
    12, 0173400, /* cmpf  */
    12, 0171400, /* modf  */
    12, 0176400, /* movie */
    05, 0175000, /* movei */
    13, 0170100, /* ldfps */
    13, 0170200, /* stfps */
    20, 0000000, /* fr0   */
    20, 0000001, /* fr1   */
    20, 0000002, /* fr2   */
    20, 0000003, /* fr3   */
    20, 0000004, /* fr4   */
    20, 0000005, /* fr5   */

    /* 11/45 operations */

    24, 0072000, /* als  (ash)  */
    24, 0073000, /* alsc (ashc) */
    24, 0070000, /* mpy  */
    24, 0070000, /* mul  */
    24, 0071000, /* div  */
    24, 0072000, /* ash  */
    24, 0073000, /* ashc */
    24, 0071000, /* dvd  */
    07, 0074000, /* xor  */
    13, 0006700, /* sxt  */
    09, 0006400, /* mark */
    25, 0077000, /* sob  */

    /* specials */

    14, 0000000, /* .byte  */
    16, 0000000, /* .even  */
    17, 0000000, /* .if    */
    18, 0000000, /* .endif */
    19, 0000000, /* .globl */
    21, 0000000, /* .text  */
    22, 0000000, /* .data  */
    23, 0000000, /* .bss   */
    26, 0000000, /* .comm  */
};

int *dotrel &symtab[0];
int *dot    &symtab[1];
int *dotdot &symtab[3];

extern int defund;
extern char *atmp1, *atmp2, *atmp3, *aout, faout;

aexit();

main(argc, argv)
int argc;
char *argv[];
{
    if (argc < 4) {
        return 1;
    } else if (argc >= 5) {
        /* globalize all undefineds (-g) */
        defund = 040;
    }
    atmp1 = argv[1];
    atmp2 = argv[2];
    atmp3 = argv[3];
    if (!(signal(2, 1) & 1)) {
        signal(2, aexit);
    }
    if ((faout = creat(aout, 0)) < 0) {
        filerr(aout);
    }
    go();
}
