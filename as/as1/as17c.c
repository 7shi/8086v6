/* translated from as17.s */

char curfbr[];
int curfb[], opfound, numval, savop;
struct { int type, val; };

/* 0 - 96 | 97 - 106 | 107 - 127 */

expres(op, type)
int *type;
{
    /* (ltype,lval) + (rtype,rval) */
    int ltype, lval, rtype, rval, isglobl;
    char opr;

    opr = '+';
    opfound = 0;
    ltype = 1; /* absolute */
    lval  = 0;

    /* sbrtn: */
    for (;;) {
        if (op < 0 || 127 < op) {
            rtype = op->type;
            rval  = op->val;
        } else if (op >= 107) { /* 0f-9f */
            rtype = op;
            lval = ltype = 0;
        } else if (op >= 97) { /* 0b-9b */
            rtype = curfbr[op - 97];
            lval  = curfb [op - 97];
            if (lval < 0) error("f");
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
                /* binop: */
                if (opr != '+') error("e");
                opr = op;
                op = readop();
                continue;

            case '[':
                /* brack: */
                rval = expres(readop(), &rtype);
                if ((op = readop()) != ']') error("f");
                break;

            case 1:
                /* exnum: */
                rtype = 1;
                rval  = numval;
                break;

            default:
                if (opfound == 0) error("e");
                savop = op;
                *type = ltype;
                return lval; /* finish: */
            }
        }

        /* oprand: */
        opfound =+ 1;
        if (opr == '^') {
            /* give left flag of right */
            ltype = rtype;
        } else {
            /* combin: */
            isglobl = (rtype | ltype) & 32;
            rtype =& 31;
            ltype =& 31;
            if (rtype == 0 || ltype == 0) {
                ltype = isglobl;
            } else if (opr == '-' && rtype == ltype) {
                ltype = isglobl | 1;
            } else if (rtype > ltype) {
                ltype = isglobl | rtype;
            } else {
                ltype = isglobl | ltype;
            }
            switch (opr) {
            case '+': lval =+  rval; break;
            case '-': lval =-  rval; break;
            case '*': lval =*  rval; break;
            case '/': lval =/  rval; break;
            case  31: lval =|  rval; break; /* |, \% */
            case '&': lval =&  rval; break;
            case  29: lval =<< rval; break; /* \< */
            case  30: lval =>> rval; break; /* \> */
            case '%': lval =%  rval; break;
            case '!': lval =+ ~rval; break;
            }
        }
        opr = '+'; /* eoprnd: */
        op = readop(); /* advanc: */
    }
}
