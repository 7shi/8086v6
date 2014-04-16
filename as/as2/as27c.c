/* translated from as27.s */

struct Op { int type, value; };

int xsymbol, esw1, passno, curfb[];
char reltp2[], reltm2[], relte2[];

expres(r4, r1, r2, r3)
int *r1, *r2, *r3;
{
    xsymbol = 0;
    return expres1(r4, r1, r2, r3);
}

int numval;

expres1(r4, r1, r2, r3)
int *r1, *r2, *r3;
{
    int r0, opr, tmp;
    opr = '+';
    *r2 = 0;
    *r3 = 1;
    for (;;) {
        r0 = r4;
        if (r0 < 0 || 127 < r0) {
            r0 = r4->type;
            if (r0 == 0 && passno) {
                error("u");
            }
            if (r0 == 32) {
                xsymbol = r4;
                *r1 = 0;
            } else {
                *r1 = r4->value;
            }
        } else {
            switch (r4) {
            case '[':
                r4 = expres1(readop(), &tmp, r1, &r0);
                if (r4 != ']') error("]");
                break;
            case   1:
                r4 = getw();
                *r1 = r4;
                r0 = 1;
                break;
            case   2:
                *r1 = numval;
                r0 = 1;
                break;
            case '^':
            case  29:
            case  30:
            case  31:
            case '+':
            case '-':
            case '*':
            case '/':
            case '&':
            case '%':
            case '!':
                if (opr != '+') error("e");
                opr = r4;
                r4 = readop();
                continue;
            default:
                if (r4 < 97) return r4;
                r0 = curfb[r4 - 97];
                *r1 = r0->value;
                r0 = r0->type;
                break;
            }
        }

        switch (opr) {
        case '^':
            *r3 = r0;
            break;
        case  29:
            *r3 = combin(r0, *r3, relte2);
            *r2 =<< *r1;
            break;
        case  30:
            *r3 = combin(r0, *r3, relte2);
            *r2 =>> *r1;
            break;
        case  31:
            *r3 = combin(r0, *r3, relte2);
            *r2 =| *r1;
            break;
        case '+':
            *r3 = combin(r0, *r3, reltp2);
            *r2 =+ *r1;
            break;
        case '-':
            *r3 = combin(r0, *r3, reltm2);
            *r2 =- *r1;
            break;
        case '*':
            *r3 = combin(r0, *r3, relte2);
            *r2 =* *r1;
            break;
        case '/':
            *r3 = combin(r0, *r3, relte2);
            *r2 =/ *r1;
            break;
        case '&':
            *r3 = combin(r0, *r3, relte2);
            *r2 =& *r1;
            break;
        case '%':
            *r3 = combin(r0, *r3, relte2);
            *r2 =% *r1;
            break;
        case '!':
            *r3 = combin(r0, *r3, relte2);
            *r2 =+ ~*r1;
            break;
        }
        opr = '+';
        r4 = readop();
    }
}

int maxtyp;

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
