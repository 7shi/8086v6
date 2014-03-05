/* translated from as17.s */

char curfbr[];
int curfb[], opfound, numval;

struct { char op0, op1; int op2; };

/* 0 - 0140 | 0141 - 0152 | 0153 - 0177
 *     0x60 | 0x61   0x6a | 0x6b   0x7f
 */

int* expres(r4, r2, r3) int r4, *r2, *r3;{
  int r0, r1, tmp;
  char sp, sp1, sp2;

  sp = '+';
  opfound = 0;
  *r2 = 0;
  *r3 = 1; 

  /* sbrtn: */
  for(;;){
    if(r4 < 0 || 0177 < r4){
      r0 = r4->op0;
      r1 = r4->op2;
    }else if(r4 >= 0141+10){ /* dic:107*/
      r0 = r4;
      *r2 = *r3 = 0;
    }else if(r4 >= 0141){ /* dic:97 */
      r0  = curfbr[r4 - 0141];
      *r2 = curfb [r4 - 0141];
      if(*r2 < 0) error("f");
    }else{
      /* mov $esw1,r1 */
      switch(r4){
        case 035:
        case 036:
        case 037:
        case '+': /*43*/
        case '-': /*45*/
        case '*': /*42*/
        case '/': /*47*/
        case '&': /*38*/
        case '%': /*37*/ 
        case '^': /*94*/ 
        case '!': /*33*/ 
          /* binop: */
          if(sp != '+'){
            error("e");
          }
          sp = r4;
          r4 = readop();
          continue;

        case '[': /*91*/ 
          /* brack: */
          sp1 = *r2;
          sp2 = *r3;
          r4 = expres(readop(), r2, r3);
          if(r4 != ']'){
            error("f");
          }
          r0 = *r3;
          r1 = *r2;
          *r3 = sp2;
          *r2 = sp1; 
          break;

        case   1:        
          /* exnum: */
          r1 = numval;
          r0 = 1;
          break;

        case   0:
        default:
          if(opfound == 0) error("e");
          return r4; /* finish: */
      }
    }

    /* oprand: */
    opfound =+ 1;
   
    switch(sp){
      case '+': /* exadd: */
        *r3 = combin(r0, *r3, 0);
        *r2 =+ r1;
        break;

      case '-': /* exsub: */
        *r3 = combin(r0, *r3, 1);
        *r2 =- r1;
        break;

      case '*': /* exmul: */
        *r3 = combin(r0, *r3, 0);
        *r2 =* r1;
        break;

      case '/': /* exdiv: */
        *r3 = combin(r0, *r3, 0);
        *r2 =/ r1;
        break;

      case 037: /* exor: */
        *r3 = combin(r0, *r3, 0);
        *r2 =| r1;
        break;

      case '&': /* exand: */
        *r3 = combin(r0, *r3, 0);
        *r2 =& r1;
        break;

      case 035: /* exlsh: */
        *r3 = combin(r0, *r3, 0);
        *r2 =<< r1;
        break;

      case 036: /* exrsh: */
        *r3 = combin(r0, *r3, 0);
        *r2 =>> r1;
        break;

      case '%': /* exmod: */
        *r3 = combin(r0, *r3, 0);
        *r2 =% r1;
        break;

      case '!': /* exnot: */
        *r3 = combin(r0, *r3, 0);
        *r2 =+ ~r1;
        break;

      case '^': /* excmbin: */
        *r3 = r0; /* give left flag of right */
        break;
    }

    sp = '+'; /* eoprnd: */
    r4 = readop(); /* advanc: */
  }
}

 /* void _combin(r0:in, r3:out, r5:in)
  *  value : r0, r3  (r3 == pc)
  *  bool  : r5
  */
combin(r0, r3, r5) {
  int v;

  v  = 040 & (r0 | r3);
  r0 = 037 & r0;
  r3 = 037 & r3;

  if(r0 == 0 || r3 == 0) return v;
  if(r5 && r0 == r3) return v | 1;
  if(r0 > r3) return v | r0;
  return v | r3;
}
