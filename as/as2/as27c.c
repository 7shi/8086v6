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
    int rel1, rel2, globl, maxtyp;
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
        rel1 = maprel(this);
        rel2 = maprel(x);
        if (rel1 == 0 || rel2 == 0) {
            this->type = 0;
        } else if (rel1 == 1 && rel2 == 1) {
            this->type = maxtyp;
        } else if (opr == '+' && rel1 == 1) {
            this->type = rel2;
        } else if ((opr == '+' || opr == '-') && rel2 == 1) {
            this->type = rel1;
        } else if (opr == '-' && rel1 <= 4 && rel1 == rel2) {
            this->type = rel1;
        } else {
            error("r");
            this->type = maxtyp;
        }
    }
}

maprel(this)
struct Op *this;
{
    int type;
    if (this->type == 32) return 32;
    type = this->type & 31;
    return type <= 4 ? type : 1;
}
