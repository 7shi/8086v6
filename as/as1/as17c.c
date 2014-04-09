/* translated from as17.s */

char curfbr[];
int curfb[], opfound, numval;
struct { int type, val; };

/* 0 - 96 | 97 - 106 | 107 - 127 */

expres(op, r2, r3)
int *r2, *r3;
{
    int type, val;
    char opr;

    opr = '+';
    opfound = 0;
    *r2 = 0;
    *r3 = 1; 

    /* sbrtn: */
    for (;;) {
        if (op < 0 || 127 < op) {
            type = op->type;
            val  = op->val;
        } else if (op >= 107) { /* 0f-9f */
            type = op;
            *r2 = *r3 = 0;
        } else if (op >= 97) { /* 0b-9b */
            type = curfbr[op - 97];
            *r2  = curfb [op - 97];
            if (*r2 < 0) error("f");
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
                    val  = r2;
                    type = r3;
                    op = expres(readop(), &val, &type);
                    if (op != ']') error("f");
                    break;

                case 1:
                    /* exnum: */
                    type = 1;
                    val  = numval;
                    break;

                default:
                    if (opfound == 0) error("e");
                    return op; /* finish: */
            }
        }

        /* oprand: */
        opfound =+ 1;

        switch (opr) {
            case '+': /* exadd: */
                *r3 = combin(type, *r3, 0);
                *r2 =+ val;
                break;

            case '-': /* exsub: */
                *r3 = combin(type, *r3, 1);
                *r2 =- val;
                break;

            case '*': /* exmul: */
                *r3 = combin(type, *r3, 0);
                *r2 =* val;
                break;

            case '/': /* exdiv: */
                *r3 = combin(type, *r3, 0);
                *r2 =/ val;
                break;

            case 31: /* exor: |, \% */
                *r3 = combin(type, *r3, 0);
                *r2 =| val;
                break;

            case '&': /* exand: */
                *r3 = combin(type, *r3, 0);
                *r2 =& val;
                break;

            case 29: /* exlsh: \< */
                *r3 = combin(type, *r3, 0);
                *r2 =<< val;
                break;

            case 30: /* exrsh: \> */
                *r3 = combin(type, *r3, 0);
                *r2 =>> val;
                break;

            case '%': /* exmod: */
                *r3 = combin(type, *r3, 0);
                *r2 =% val;
                break;

            case '!': /* exnot: */
                *r3 = combin(type, *r3, 0);
                *r2 =+ ~val;
                break;

            case '^': /* excmbin: */
                *r3 = type; /* give left flag of right */
                break;
        }

        opr = '+'; /* eoprnd: */
        op = readop(); /* advanc: */
    }
}

combin(type, r3, r5) {
    int v;

    v  = (type | r3) & 32;
    type =& 31;
    r3 =& 31;

    if (type == 0 || r3 == 0) return v;
    if (r5 && type == r3) return v | 1;
    if (type > r3) return v | type;
    return v | r3;
}
