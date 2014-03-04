/* translated from as17.s */

char *curfbr;
int *curfb;
int opfound;
char exsw2[];
int numval;
struct { char op0, op1; int op2; };

/* 0 - 0140 | 0141 - 0153 | 0154 - 0177
 *     0x60 | 0x61   0x6b | 0x6c   0x7f
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
    r0 = r4;
    if(r0 < 0 || 0177 < r0){
      r0 = r4->op0;
      r1 = r4->op2;
    }else if(r4 >= 0141){ /* dic:97 */
      if(r4 < 0141+10){ /* dic:107*/
        r0  = curfbr[r4 - 0141];
        *r2 = curfb [r4 - 0141];
        if(*r2 < 0){
          error('f');
        }
      }else{
        *r2 = *r3 = 0;
      }
    }else{
      /* mov $esw1,r1; */
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
          if(sp != '+'){
            error('e');
          }
          sp = r4;
          r4 = readop();
          continue;

        case '[': /*91*/ 
          sp1 = *r2;
          sp2 = *r3;
          r4 = expres(readop(), r2, r3);
          if(r4 != ']'){
            error('f');
          }
          r0 = *r3;
          r1 = *r2;
          *r3 = sp2;
          *r2 = sp1; 
          break;

        case   1:        
          r1 = numval;
          r0 = 1;
          break;

        case   0:
        default:
          if(opfound == 0) error('e');
          return r4;
      }
    }

    opfound =+ 1;
   
    switch(sp){
      case '+': ;
        *r3 = combin(r0, *r3, 0);
        *r2 =+ r1;
        break;

      case '-': 
        *r3 = combin(r0, *r3, 1);
        *r2 =- r1;
        break;

      case '*': 
        *r3 = combin(r0, *r3, 0);
      
        /* TODO: mpy r2,r1 --> r0 untouched */
        /* mul(mpy) */
        /* R/Rv1 = R * src ---> r2/r3 = r2 * r1*/
        /* printf("div: r2r3 = %x %x\n", r2 * r1); */
        r1 = r1 * *r2;
        *r2 = r1; 
        break;

      case '/': 
        *r3 = combin(r0, *r3, 0);
        tmp = r1;
        r1 = *r2;
        r0 = 0;
      
        /* div */
        /* r0 = r1 / (sp)=tmp;  div result   */
        /* r1 = r1 % (sp)=tmp;  div reminder */
        while(r1 >= tmp){
          r1 = r1 - tmp;
          r0++;
        }
      
        *r2 = r0;
        break;

      case 037: 
        *r3 = combin(r0, *r3, 0);
        *r2 =| r1;
        break;

      case '&': 
        *r3 = combin(r0, *r3, 0);
        r1 = ~r1;
        *r2 = (~r1) & *r2;
        break;

      case 036: 
        r1 = -r1;
        if(r1){
          r1++;
          *r2 = ((*r2 >> 1) & 177) | (*r2 << 15);
        }
      case 035: 
        *r3 = combin(r0, *r3, 0);
        if(r1>0){
          *r2 = *r2 << r1;
        }else{
          *r2 = *r2 >> (-r1);
        }
        break;

      case '%': 
        *r3 = combin(r0, *r3, 0);
        sp1 = r1;
        r1 = *r2;
        r0 = 0;
        /*TODO: dvd (sp)+,r0     / remove auto variable2  */ 
        /* div */
        /* r0 = r1 / (sp)=tmp;  div result   */
        /* r1 = r1 % (sp)=tmp;  div reminder */
        while(r1 >= sp1){
          r1 = r1 - sp1;
          r0++;
        }
        *r2 = r1;
        break;

      case '!': 
        *r3 = combin(r0, *r3, 0);
        r1 = ~r1;
        *r2 =+ r1;
        break;

      case '^': 
        *r3 = r0;
        break;
    }

    sp = '+';
    r4 = readop();
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
