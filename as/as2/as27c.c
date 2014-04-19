/* translated from as27.s */

struct Op { int type, value; };

int xsymbol;

expres(r4, r2, r3)
int *r2, *r3;
{
    struct Op x;
    xsymbol = 0;
    r4 = expres1(&x, r4);
    *r2 = x.value;
    *r3 = x.type;
    return r4;
}

int numval, esw1, passno, curfb[];
char reltp2[], reltm2[], relte2[];

expres1(this, r4)
struct Op *this;
{
    struct Op x;
    int r0, r1, opr;
    opr = '+';
    this->type  = 1;
    this->value = 0;
    for (;;) {
        r0 = r4;
        if (r0 < 0 || 127 < r0) {
            r0 = r4->type;
            if (r0 == 0 && passno) {
                error("u");
            }
            if (r0 == 32) {
                xsymbol = r4;
                r1 = 0;
            } else {
                r1 = r4->value;
            }
        } else if (r4 >= 97) {
            r0 = curfb[r4 - 97];
            r1 = r0->value;
            r0 = r0->type;
        } else {
            switch (r4) {
            case '[':
                r4 = expres1(&x, readop());
                r0 = x.type;
                r1 = x.value;
                if (r4 != ']') error("]");
                break;
            case   1:
                r1 = getw();
                r0 = 1;
                break;
            case   2:
                r1 = numval;
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
                return r4;
            }
        }

        switch (opr) {
        case '^':
            this->type = r0;
            break;
        case  29:
            combin(this, r0, relte2);
            this->value =<< r1;
            break;
        case  30:
            combin(this, r0, relte2);
            this->value =>> r1;
            break;
        case  31:
            combin(this, r0, relte2);
            this->value =| r1;
            break;
        case '+':
            combin(this, r0, reltp2);
            this->value =+ r1;
            break;
        case '-':
            combin(this, r0, reltm2);
            this->value =- r1;
            break;
        case '*':
            combin(this, r0, relte2);
            this->value =* r1;
            break;
        case '/':
            combin(this, r0, relte2);
            this->value =/ r1;
            break;
        case '&':
            combin(this, r0, relte2);
            this->value =& r1;
            break;
        case '%':
            combin(this, r0, relte2);
            this->value =% r1;
            break;
        case '!':
            combin(this, r0, relte2);
            this->value =+ ~r1;
            break;
        }
        opr = '+';
        r4 = readop();
    }
}

int maxtyp;

combin(this, r0, r5)
struct Op *this;
char *r5;
{
    int r1, globl, tmp;
    if (!passno) {
        globl = (r0 | this->type) & 32;
        r0 =& 31;
        this->type =& 31;
        if (r0 > this->type) {
            tmp = r0;
            r0 = this->type;
            this->type = tmp;
        }
        if (!r0) {
            this->type = 0;
        } else if (r5 == reltm2 && r0 == this->type) {
            this->type = 1;
        }
        this->type =| globl;
    } else {
        maxtyp = 0;
        r1 = maprel(r0) * 6;
        this->type = r5[maprel(this->type) + r1];
        if (this->type < 0) {
            if (this->type != -1) error("r");
            this->type = maxtyp;
        }
    }
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
