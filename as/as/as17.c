/* translated from as17.s */

struct Op { char type, num; int value; };

char curfbr[];
int curfb[], numval, savop;

expres(this, op)
struct Op *this;
{
    struct Op x;
    char opr;
    int opfound;

    this->type  = 1; /* absolute */
    this->num   = 0;
    this->value = 0;

    opr = '+';
    opfound = 0;

    for (;;) {
        if (issym(op)) {
            x.type  = op->type;
            x.value = op->value;
        } else if ('a' <= op && op <= 'j') { /* 0b-9b */
            x.type  = curfbr[op - 'a'];
            x.value = curfb [op - 'a'];
            if (x.value == -1) error("f");
        } else if ('k' <= op && op <= 't') { /* 0f-9f */
            x.type  = op;
            x.value = 0;
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
                if (opr != '+') error("e");
                opr = op;
                op = readop();
                continue;
            case '[':
                expres(&x, readop());
                if (!checkop(']')) error("]");
                break;
            case 1:
                x.type  = 1;
                x.value = numval;
                break;
            default:
                if (opfound == 0) error("e");
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
    int globl;
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
}
