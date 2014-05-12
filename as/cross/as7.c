#include <stdint.h>

struct Sym { char type, num; short value; };
extern struct Sym curfbr[], *curfb[], *nxtfb[], *xsymbol;

union Op { intptr_t op; struct Sym *sym; };

extern intptr_t savop;

expres(this, op)
struct Sym *this;
union Op op;
{
    xsymbol = 0;
    expres1(this, op);
}

extern int numval, passno;

expres1(this, op)
struct Sym *this;
union Op op;
{
    struct Sym x, *fb;
    char opr;
    int opfound;

    this->type  = 1; /* absolute */
    this->num   = 0;
    this->value = 0;

    opr = '+';
    opfound = 0;

    for (;;) {
        if (issym(op)) {
            x.type = op.sym->type;
            if (x.type == 0 && passno == 2) {
                error("u");
            }
            if (passno && x.type == 32) {
                xsymbol = op.sym;
                x.value = 0;
            } else {
                x.value = op.sym->value;
            }
        } else if ('a' <= op.op && op.op <= 'j') { /* 0b-9b */
            if (passno == 0) {
                fb = &curfbr[op.op - 'a'];
                x.type  = fb->type;
                x.value = fb->value;
                if (x.value == -1) error("f");
            } else {
                fb = curfb[op.op - 'a'];
                x.type  = fb->type;
                x.value = fb->value;
            }
        } else if ('k' <= op.op && op.op <= 't') { /* 0f-9f */
            if (passno == 0) {
                x.type  = op.op;
                x.value = 0;
            } else {
                fb = nxtfb[op.op - 'k'];
                x.type  = fb->type;
                x.value = fb->value;
            }
        } else {
            switch (op.op) {
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
                if (opr != '+') error("e");
                opr = op.op;
                op.op = readop();
                continue;
            case '[':
                expres1(&x, readop());
                if (!checkop(']')) error("]");
                break;
            case 1:
                x.type  = 1;
                x.value = numval;
                break;
            default:
                savop = op.op;
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
            case  29: this->value <<=  x.value; break; /* \< */
            case  30: this->value >>=  x.value; break; /* \> */
            case  31: this->value  |=  x.value; break; /* |, \% */
            case '+': this->value  +=  x.value; break;
            case '-': this->value  -=  x.value; break;
            case '*': this->value  *=  x.value; break;
            case '/': this->value  /=  x.value; break;
            case '&': this->value  &=  x.value; break;
            case '%': this->value  %=  x.value; break;
            case '!': this->value  += ~x.value; break;
            }
        }
        opr = '+';
        op.op = readop();
    }
}

combin(this, x, opr)
struct Sym *this, *x;
{
    int rel1, rel2, globl, maxtyp;
    if (passno < 2) {
        globl = (this->type | x->type) & 32;
        this->type &= 31;
        x   ->type &= 31;
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
            error("r");
            this->type = maxtyp;
        }
    }
}

maprel(this)
struct Sym *this;
{
    int type;
    if (this->type == 32) return 32;
    type = this->type & 31;
    return type <= 4 ? type : 1;
}
