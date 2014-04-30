/* translated from as27.s */

struct Op { int type, value; };

int savop;
char *xsymbol;

expres(this, op)
struct Op *this;
{
    xsymbol = 0;
    expres1(this, op);
}

int numval, esw1, passno, curfb[];
char reltp2[], reltm2[], relte2[];

expres1(this, op)
struct Op *this;
{
    struct Op x, *fb;
    int opr;
    opr = '+';
    this->type  = 1;
    this->value = 0;
    for (;;) {
        if (issym(op)) {
            x.type = op->type;
            if (x.type == 0 && passno) {
                error("u");
            }
            if (x.type == 32) {
                xsymbol = op;
                x.value = 0;
            } else {
                x.value = op->value;
            }
        } else if (op >= 97) {
            fb = curfb[op - 97];
            x.type  = fb->type;
            x.value = fb->value;
        } else {
            switch (op) {
            case '[':
                expres1(&x, readop());
                if (!checkop(']')) error("]");
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
                opr = op;
                op = readop();
                continue;
            default:
                savop = op;
                return;
            }
        }

        if (opr == '^') {
            this->type = x.type;
        } else {
            combin(this, &x, opr);
            switch (opr) {
            case  29: this->value =<< x.value; break;
            case  30: this->value =>> x.value; break;
            case  31: this->value =|  x.value; break;
            case '+': this->value =+  x.value; break;
            case '-': this->value =-  x.value; break;
            case '*': this->value =*  x.value; break;
            case '/': this->value =/  x.value; break;
            case '&': this->value =&  x.value; break;
            case '%': this->value =%  x.value; break;
            case '!': this->value =+ ~x.value; break;
            }
        }
        opr = '+';
        op = readop();
    }
}

combin(this, x, opr)
struct Op *this, *x;
{
    int rel, globl, tmp, maxtyp;
    if (!passno) {
        globl = (this->type | x->type) & 32;
        this->type =& 31;
        x   ->type =& 31;
        if (this->type == 0 || x->type == 0) {
            this->type = globl;
        } else if (opr == '-' && this->type == x->type) {
            this->type = globl | 1;
        } else {
            this->type = globl | max(this->type, x->type);
        }
    } else {
        maxtyp = max(this->type & 31, x->type & 31);
        rel = maprel(this) + maprel(x) * 6;
        switch (opr) {
        case '+': this->type = reltp2[rel]; break;
        case '-': this->type = reltm2[rel]; break;
        default : this->type = relte2[rel]; break;
        }
        if (this->type < 0) {
            if (this->type == -2) error("r");
            this->type = maxtyp;
        }
    }
}

maprel(this)
struct Op *this;
{
    int type;
    if (this->type == 32) return 5;
    type = this->type & 31;
    return type <= 5 ? type : 1;
}

/* X = -2, M = -1 */

char reltp2[] {
    0,  0,  0,  0,  0,  0,
    0, -1,  2,  3,  4, 32,
    0,  2, -2, -2, -2, -2,
    0,  3, -2, -2, -2, -2,
    0,  4, -2, -2, -2, -2,
    0, 32, -2, -2, -2, -2
};

char reltm2[] {
    0,  0,  0,  0,  0,  0,
    0, -1,  2,  3,  4, 32,
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
