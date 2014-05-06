/* translated from as27.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[];

int savop;
char *xsymbol, curfbr[];

expres(this, op)
struct Op *this;
{
    xsymbol = 0;
    expres1(this, op);
}

int numval, passno;

expres1(this, op)
struct Op *this;
{
    struct Op x, *fb;
    char opr;
    int opfound;

    this->type  = 1; /* absolute */
    this->num   = 0;
    this->value = 0;

    opr = '+';
    opfound = 0;

    for (;;) {
        if (issym(op)) {
            x.type = op->type;
            if (x.type == 0 && passno == 2) {
                _error("u");
            }
            if (passno && x.type == 32) {
                xsymbol = op;
                x.value = 0;
            } else {
                x.value = op->value;
            }
        } else if ('a' <= op && op <= 'j') { /* 0b-9b */
            if (passno == 0) {
                x.type  = curfbr[op - 'a'];
                x.value = curfb [op - 'a'];
                if (x.value == -1) error("f");
            } else {
                fb = curfb[op - 'a'];
                x.type  = fb->type;
                x.value = fb->value;
            }
        } else if ('k' <= op && op <= 't') { /* 0f-9f */
            if (passno == 0) {
                x.type  = op;
                x.value = 0;
            } else {
                fb = nxtfb[op - 'k'];
                x.type  = fb->type;
                x.value = fb->value;
            }
        } else {
            switch (op) {
            case '^':
            case  29: /* \< */
            case  30: /* \> */
            case  31: /* |, \% */
            case '+':
            case '-':
            case '*':
            case '/':
            case '&':
            case '%':
            case '!':
                if (opr != '+') _error("e");
                opr = op;
                op = readop();
                continue;
            case '[':
                expres1(&x, readop());
                if (!checkop(']')) _error("]");
                break;
            case 1:
                x.type  = 1;
                x.value = passno == 0 ? numval : getw();
                break;
            case 2:
                if (passno) {
                    x.type  = 1;
                    x.value = numval;
                    break;
                }
            default:
                savop = op;
                return;
            }
        }

        ++opfound;
        if (opr == '^') {
            /* give left flag of right */
            this->type = x.type;
        } else {
            combin(this, &x, opr);
            switch (opr) {
            case  29: this->value =<< x.value; break; /* \< */
            case  30: this->value =>> x.value; break; /* \> */
            case  31: this->value =|  x.value; break; /* |, \% */
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
    if (passno < 2) {
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
            this->type = 1;
        } else {
            _error("r");
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
