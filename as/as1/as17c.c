/* translated from as17.s */

char *curfbr;
int *curfb;
int opfound;
char exsw2[];
int numval;

/* 0 - 0140 | 0141 - 0153 | 0154 - 0177
 *     0x60 | 0x61   0x6b | 0x6c   0x7f
 */

int* expres(r4, r2, r3) int *r4, *r2, *r3;{
  int r0;
  int r1;
  int tmp;
  char* c_r4;
  char sp;
  char sp1;
  char sp2;

  sp = '+';
  opfound = 0;
  *r2 = 0;
  *r3 = 1; 
  /* write(0,"-->expres\n",10); */

sbrtn:
  r0 = r4;
  c_r4 = r4;

  /* printf("%d %d\n", r0, r4); */
  /*  */
  if(r0 < 0 || 0177 < r0){
    /* write(0,">betwin<\n",9); */
    /* TODO:
     * movb (r4),r0
     *  r4[0] & 0xFF >>> r0 ?
     *     or
     *  *(r4 & 0xFF) >>> r0 ? */
    r0 = r4[0] & 0377;
    r1 = r4[1];

    /* TODO: r1 = *(r4 + 2); */
    goto oprand;
  }

  tmp = r4;
  if(tmp >= 0141){ /* dic:97 */
    if(tmp < 0141+012){ /* dic:107*/

      tmp = r4;
      tmp =- 0141;
      r0  = curfbr[tmp] & 0377;
/*
      tmp = curfbr - 0141;
      r0 = c_r4[tmp] & 0377;

      tmp = r4;
      tmp = tmp - 0141;
      r0 = curfbr[tmp] & 0377;

      tmp = r4[2*0141];
      r0 = (curfbr - tmp) & 0377;
*/
      tmp = r4;
      tmp = tmp << 1;
      r4 = tmp;
      tmp = r4;
      tmp =- 2*0141;
      *r2 = r4[tmp/2];
/*
      tmp = r4;
      tmp = tmp - 2*2*0141;
      *r2 = curfb[2*tmp];

      tmp = r4;
      tmp = tmp * 2;
      r4 = tmp;
      tmp = r4[2*2*0141];
      *r2 = curfb - tmp;
*/
      tmp = curfb;
      if(*r2 >= 0){
        goto oprand;
      }else{
        error('f');
        goto oprand;
      }
    }
    *r3 = 0;
    *r2 = 0;
    goto oprand;
  }
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
      goto advanc;

    case '[': /*91*/ 
      sp1 = *r2;
      sp2 = *r3;
      r4 = expres(readop(), r2, r3);
      tmp = r4;
      if(tmp != ']'){
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
      goto finish;
  }

oprand:
  opfound =+ 1;
 
  switch(sp){
    case '+': ;
      goto exadd;
    case '-': 
      goto exsub;
    case '*': 
      goto exmul;
    case '/': 
      goto exdiv;
    case 037: 
      goto exor;
    case '&': 
      goto exand;
    case 035: 
      goto exlsh;
    case 036: 
      goto exrsh;
    case '%': 
      goto exmod;
    case '!': 
      goto exnot;
    case '^': 
      goto excmbin;
    case   0:
    default : 
      break;
  }

  goto eoprnd; 

excmbin:
  /* write(0,"excmbin\n",8); */
  *r3 = r0;
  goto eoprnd;

exrsh:
  /* write(0,"exrsh\n",6); */
  r1 = -r1;
  if(r1 == 0){
    goto exlsh;
  }
  r1++;
  *r2 = ((*r2 >> 1) & 177) | (*r2 << 15);
  goto exlsh;
 
exlsh:
  /* write(0,"exlsh\n",6); */
  combin(r0, r3, 0);
  if(r1>0){
    *r2 = *r2 << r1;
  }else{
    *r2 = *r2 >> (-r1);
  }
  goto eoprnd; 


exmod:
  /* write(0,"exmod\n",6);*/
  combin(r0, r3, 0);
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
  goto eoprnd;

exadd:
  /* write(0,"exadd\n",6); */

  combin(r0, r3, 0);

  *r2 =+ r1;
  goto eoprnd; 

exsub:
  /* write(0,"exsub\n",6); */

  combin(r0, r3, 1);
  *r2 =- r1;
  goto eoprnd; 

exmul:
  /* write(0,"exmul\n",6); */
  combin(r0, r3, 0);

  /* TODO: mpy r2,r1 --> r0 untouched */
  /* mul(mpy) */
  /* R/Rv1 = R * src ---> r2/r3 = r2 * r1*/
  /* printf("div: r2r3 = %x %x\n", r2 * r1); */
  r1 = r1 * *r2;
  *r2 = r1; 
  goto eoprnd; 

exdiv:
  /* write(0,"exdiv\n",6); */
  combin(r0, r3, 0);
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
  goto eoprnd; 

exor:
  /* write(0,"exor\n",5); */
  combin(r0, r3, 0);
  *r2 =| r1;
  goto eoprnd; 

exand:
 /* write(0,"exand\n",6); */
  combin(r0, r3, 0);
  r1 = ~r1;
  *r2 = (~r1) & *r2;
  goto eoprnd; 

exnot:
  /* write(0,"exnot!!!!!\n",11); */
  combin(r0, r3, 0);
  r1 = ~r1;
  *r2 =+ r1;
  goto eoprnd;

eoprnd:
  /* write(0,"eoprnd\n",7); */
  sp = '+';
  goto advanc;

advanc:
  r4 = readop();
  goto sbrtn;

finish:

  return r4;
}

 /* void _combin(r0:in, r3:out, r5:in)
  *  value     : r0,r3  (r3 == pc)
  *  reference : r5
  */
combin(r0, r3, r5) int* r3;{
  int local1;
  int local2;

  local1 = r0;
  local1 = local1 | *r3;

  local1 = (040) & local1;
  r0     = (037) & r0;
  (*r3)     = (037) & (*r3);

  if(r0 > (*r3)){
    local2 = r0;
    r0 = (*r3);
    (*r3) = local2;
  }

  /* 1: */
  if(r0 == 0){ 
    (*r3) = 0;
  }else if(r5 != 0 && r0 == (*r3)){
    (*r3) = 1;
  }

  (*r3) = (*r3) | local1;
}

