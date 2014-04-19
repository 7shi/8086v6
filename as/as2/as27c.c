/* translated from as27.s */

struct Op { int type, value; };

int xsymbol;

expres(this, r4)
struct Op *this;
{
    xsymbol = 0;
    return expres1(this, r4);
}

int numval, esw1, passno, curfb[];
char reltp2[], reltm2[], relte2[];

expres1(this, r4)
struct Op *this;
{
    struct Op x, *fb;
    int opr;
    opr = '+';
    this->type  = 1;
    this->value = 0;
    for (;;) {
        if (r4 < 0 || 127 < r4) {
            x.type = r4->type;
            if (x.type == 0 && passno) {
                error("u");
            }
            if (x.type == 32) {
                xsymbol = r4;
                x.value = 0;
            } else {
                x.value = r4->value;
            }
        } else if (r4 >= 97) {
            fb = curfb[r4 - 97];
            x.type  = fb->type;
            x.value = fb->value;
        } else {
            switch (r4) {
            case '[':
                r4 = expres1(&x, readop());
                if (r4 != ']') error("]");
                break;
            case   1:
                x.type  = 1;
                x.value = getw();
                break;
            case   2:
                x.type  = 1;
                x.value = numval;
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
        case '^': this->type = x.type; break;
        case  29: combin(this, &x, relte2); this->value =<< x.value; break;
        case  30: combin(this, &x, relte2); this->value =>> x.value; break;
        case  31: combin(this, &x, relte2); this->value =|  x.value; break;
        case '+': combin(this, &x, reltp2); this->value =+  x.value; break;
        case '-': combin(this, &x, reltm2); this->value =-  x.value; break;
        case '*': combin(this, &x, relte2); this->value =*  x.value; break;
        case '/': combin(this, &x, relte2); this->value =/  x.value; break;
        case '&': combin(this, &x, relte2); this->value =&  x.value; break;
        case '%': combin(this, &x, relte2); this->value =%  x.value; break;
        case '!': combin(this, &x, relte2); this->value =+ ~x.value; break;
        }
        opr = '+';
        r4 = readop();
    }
}

int maxtyp;

combin(this, x, r5)
struct Op *this, *x;
char *r5;
{
    int r0, r1, globl, tmp;
    r0 = x->type;
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
