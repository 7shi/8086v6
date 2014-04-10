/* translated from as17.s */

struct Op { int type, value; };

char curfbr[];
int curfb[], opfound, numval, savop;

expres(this, op)
struct Op *this;
{
    struct Op x;
    char opr;

    this->type  = 1; /* absolute */
    this->value = 0;

    opr = '+';
    opfound = 0;

    /* sbrtn: */
    for (;;) {
        if (op < 0 || 127 < op) {
            x.type  = op->type;
            x.value = op->value;
        } else if ('a' <= op && op <= 'j') { /* 0b-9b */
            x.type  = curfbr[op - 97];
            x.value = curfb [op - 97];
            if (x.value < 0) error("f");
        } else if ('k' <= op && op <= 't') { /* 0f-9f */
            x.type  = op;
            x.value = 0;
        } else {
            switch (op) {
            case 29: /* \< */
            case 30: /* \> */
            case 31: /* |, \% */
            case '+':
            case '-':
            case '*':
            case '/':
            case '&':
            case '%':
            case '^':
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

        /* oprand: */
        opfound =+ 1;
        if (opr == '^') {
            /* give left flag of right */
            this->type = x.type;
        } else {
            combin(this, &x, opr);
            switch (opr) {
            case '+': this->value =+  x.value; break;
            case '-': this->value =-  x.value; break;
            case '*': this->value =*  x.value; break;
            case '/': this->value =/  x.value; break;
            case  31: this->value =|  x.value; break; /* |, \% */
            case '&': this->value =&  x.value; break;
            case  29: this->value =<< x.value; break; /* \< */
            case  30: this->value =>> x.value; break; /* \> */
            case '%': this->value =%  x.value; break;
            case '!': this->value =+ ~x.value; break;
            }
        }
        opr = '+'; /* eoprnd: */
        op = readop(); /* advanc: */
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
    } else if (this->type >= x->type) {
        this->type = globl | this->type;
    } else {
        this->type = globl | x->type;
    }
}
