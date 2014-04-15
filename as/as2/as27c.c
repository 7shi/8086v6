/* translated from as27.s */

int passno, maxtyp;
char reltp2[], reltm2[], relte2[];

combin(r0, r3, r5)
char *r5;
{
    int r1, globl, tmp;
    if (!passno) {
        globl = (r0 | r3) & 32;
        r0 =& 31;
        r3 =& 31;
        if (r0 > r3) {
            tmp = r0;
            r0 = r3;
            r3 = tmp;
        }
        if (!r0) {
            r3 = 0;
        } else if (r5 == reltm2 && r0 == r3) {
            r3 = 1;
        }
        r3 =| globl;
    } else {
        maxtyp = 0;
        r1 = maprel(r0) * 6;
        r3 = r5[maprel(r3) + r1];
        if (r3 < 0) {
            if (r3 != -1) error("r");
            r3 = maxtyp;
        }
    }
    return r3;
}

int maxtyp;

maprel(r0)
{
    if (r0 == 32) return 5;
    r0 =& 31;
    if (maxtyp < r0) maxtyp = r0;
    if (r0 > 5) return 1;
    return r0;
}

/* X = -2, M = -1 */

char reltp2[] {
    0,  0,  0,  0,  0,  0,
    0, -1,  2,  3,  4, 40,
    0,  2, -2, -2, -2, -2,
    0,  3, -2, -2, -2, -2,
    0,  4, -2, -2, -2, -2,
    0, 40, -2, -2, -2, -2
};

char reltm2[] {
    0,  0,  0,  0,  0,  0,
    0, -1,  2,  3,  4, 40,
    0, -2,  1, -2, -2, -2,
    0, -2, -2,  1, -2, -2,
    0, -2, -2, -2,  1, -2,
    0, -2, -2, -2, -2, -2
};

char relte2[] {
    0,  0,  0,  0,  0,  0,
    0, -1, -2, -2, -2, -2,
    0, -2, -2, -2, -2, -2,
    0, -2, -2, -2, -2, -2,
    0, -2, -2, -2, -2, -2,
    0, -2, -2, -2, -2, -2
};
