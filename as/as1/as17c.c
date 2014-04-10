/* translated from as17.s */

struct Op { int type, value; };

char curfbr[];
int curfb[], opfound, numval, savop;

expres(this, op)
struct Op *this;
{
    int type, value, isglobl;
    char opr;

    this->type  = 1; /* absolute */
    this->value = 0;

    opr = '+';
    opfound = 0;

    /* sbrtn: */
    for (;;) {
        if (op < 0 || 127 < op) {
            type = op->type;
            value  = op->value;
        } else if ('a' <= op && op <= 'j') { /* 0b-9b */
            type = curfbr[op - 97];
            this->value  = curfb [op - 97];
            if (this->value < 0) error("f");
        } else if ('k' <= op && op <= 't') { /* 0f-9f */
            type = op;
            this->value = this->type = 0;
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
                value = expres(readop(), &type);
                if ((op = readop()) != ']') error("f");
                break;
            case 1:
                type  = 1;
                value = numval;
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
            this->type = type;
        } else {
            /* combin: */
            isglobl = (type | this->type) & 32;
            type =& 31;
            this->type =& 31;
            if (type == 0 || this->type == 0) {
                this->type = isglobl;
            } else if (opr == '-' && type == this->type) {
                this->type = isglobl | 1;
            } else if (type > this->type) {
                this->type = isglobl | type;
            } else {
                this->type = isglobl | this->type;
            }
            switch (opr) {
            case '+': this->value =+  value; break;
            case '-': this->value =-  value; break;
            case '*': this->value =*  value; break;
            case '/': this->value =/  value; break;
            case  31: this->value =|  value; break; /* |, \% */
            case '&': this->value =&  value; break;
            case  29: this->value =<< value; break; /* \< */
            case  30: this->value =>> value; break; /* \> */
            case '%': this->value =%  value; break;
            case '!': this->value =+ ~value; break;
            }
        }
        opr = '+'; /* eoprnd: */
        op = readop(); /* advanc: */
    }
}
