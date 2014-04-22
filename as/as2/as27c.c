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
                expres1(&x, readop()); op = readop();
                if (op != ']') error("]");
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
        op = readop();
    }
}

combin(this, x, map)
struct Op *this, *x;
char *map;
{
    int type, rel, globl, tmp, maxtyp;
    type = x->type;
    if (!passno) {
        globl = (type | this->type) & 32;
        type =& 31;
        this->type =& 31;
        if (type > this->type) {
            tmp = type;
            type = this->type;
            this->type = tmp;
        }
        if (!type) {
            this->type = 0;
        } else if (map == reltm2 && type == this->type) {
            this->type = 1;
        }
        this->type =| globl;
    } else {
        maxtyp = 0;
        rel = maprel(type, &maxtyp) * 6;
        this->type = map[maprel(this->type, &maxtyp) + rel];
        if (this->type < 0) {
            if (this->type != -1) error("r");
            this->type = maxtyp;
        }
    }
}

maprel(type, maxtyp)
int *maxtyp;
{
    if (type == 32) return 5;
    type =& 31;
    if (*maxtyp < type) *maxtyp = type;
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
