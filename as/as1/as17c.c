/* translated from as17.s */

int curfbr[];
int curfb[];
int opfound;
char exsw2[];
int numval;


int btwn(r0, pc1, pc2) int r0; int pc1; int pc2;{
  return pc1 <= r0 && r0 <= pc2;
}

/* 0 - 0140 | 0141 - 0153 | 0154 - 0177
 *     0x60 | 0x61   0x6b | 0x6c   0x7f
 */

int* cexprs(r2, r3, r4) int* r2; int* r3; int* r4;{
  register int r0;
  register int r1;
  /* register int r2; */
  /* int r5; */
  int tmp;
  /* int r3; */
  char* c_r4;
  char sp;
  char sp1;
  char sp2;

  sp = '+';
  opfound = 0;
  *r2 = 0;
  *r3 = 1; 
  write(0,"-->cexprs\n",10);

sbrtn:
  r0 = r4;
  c_r4 = r4;

  write(0,"sbrtn\n",6);
  /* printf("%d %d\n", r0, r4); */

  /*  */
  if(btwn(r0, 0, 0177) != 1){
    write(0,">betwin<\n",9);
    /* r0 = (r0 & 0177400) | *c_r4; */
    /* TODO:
     * movb (r4),r0
     *  r4[0] & 0xFF >>> r0 ?
     *     or
     *  *(r4 & 0xFF) >>> r0 ? */
    r0 = (*r4) & 0377;
    r1 = *(r4 + 4);
    /*TODO: r1 = *(r4 + 2); */
    goto oprand;
  }

  write(0,"<1>",3);
  tmp = r4;
  if(tmp >= 0141){ /* dic:97 */
    write(0,"<2>",3);
    if(tmp < 0141+012){ /* dic:107*/
      write(0,"ooo\n",4);
      /*
      tmp = curfbr - 0141;
      r0 = (r0 & 0177400) | c_r4[tmp];
      r4 << 1;
      tmp = curfb - 2*0141;
      r2 = r4[tmp];
      */
      tmp = r4;
      tmp =- 0141;
      r0 = curfbr[tmp] & 0377;
      tmp = r4;
      tmp = tmp << 1;
      r4 = tmp;
      *r2 = curfb[tmp];
      if(*r2 > 0){
        goto oprand;
      }else{
        error('f');
        /* TODO */
        write(0, "r2\n", 3);
        /* exit(1); */
        goto oprand;
      }
    }
    write(0,"---\n",4);
    *r3 = 0;
    *r2 = 0;
    goto oprand;
  }
  write(0,"0<a<0141\n",9);
  /* mov $esw1,r1; */

  switch(r4){
    case '+': /*43*/
    case '-': /*45*/
    case '*': /*42*/
    case '/': /*47*/
    case '&': /*38*/
    case 037:
    case 035:
    case 036:
    case '%': /*37*/ 
      goto binop;
    case '[': /*91*/ 
      goto brack;
    case '^': /*94*/ 
      goto binop;
    case   1:        
      /* exnum(r0, r1, r2, r3, &r4, sp); return; */
      goto exnum;
    case '!': /*33*/ 
      goto binop;
    case   0:
    default:
      break;
  }


  if(opfound != 0){
    write(0,"to be finished at cexpres\n", 26);
    goto finish;
  }else{
    /* write(0,"to be errored at cexpres\n",25); */
    /* TODO: should be changed to errore() */
    error('e');
   /* TODO */
    write(0, "opfound\n", 8);
    goto finish; /* TODO: */
  }

binop:
  write(0,"binop\n",6);

  if(sp != '+'){
    /* TODO: should be changed to errore() */
    error('e');
    /* TODO */
    /* write(0, "binop\n", 6); */
    /* exit(1); */
    /*errore();*/
  }
  sp = r4;

  goto advanc; 

exnum:
  write(0,"exnum\n",6);

  r1 = numval;
  r0 = 1;
  goto oprand;

brack:
  write(0, "brack\n", 6);
  sp1 = *r2;
  sp2 = *r3;
  write(0,"->cexprs\n",9);
  r4 = cexprs(r2, r3, readop_());
  write(0,"->cexprs-end\n",13);

  tmp = r4;
  if(tmp != ']'){
    error('f');
    /* TODO */
    /* write(0, "brack\n", 6); */
  }
  r0 = *r3;
  r1 = *r2;
  *r3 = sp2;
  *r2 = sp1; 
  goto oprand;

oprand:
  /*
  printf("--r0 r1 r2 :%x %x %x\n", r0, r1, r2);
  printf("--r3 r4 -- :%x %x\n", r3, r4);
  printf("---------- :%c(%d)\n", sp, sp);
  */
  /* oprand(r0, r1, r2, r3, r4, sp); */
  
  write(0,"oprand\n",7);

  /* r5 = exsw2 */; 
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

  /* TODO: */
  goto eoprnd; 

exadd:
  /* write(0,"exadd\n",6); */

  r0 = combin(r0, r3, 0);
  *r2 =+ r1;
  goto eoprnd; 

exsub:
  /* write(0,"exsub\n",6); */

  r0 = combin(r0, r3, 0);
  *r2 =- r1;
  goto eoprnd; 

exmul:
  /* write(0,"exmul\n",6); */
  r0 = combin(r0, r3, 0);

  /* TODO: mpy r2,r1 --> r0 untouched */
  /* mul(mpy) */
  /* R/Rv1 = R * src ---> r2/r3 = r2 * r1*/
  /* printf("div: r2r3 = %x %x\n", r2 * r1); */
  r1 = r1 * *r2;
  *r2 = r1; 
  goto eoprnd; 

exdiv:
  /* write(0,"exdiv\n",6); */
  r0 = combin(r0, r3, 0);
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
  r0 = combin(r0, r3, 0);
  *r2 =| r1;
  goto eoprnd; 

exand:
  /* write(0,"exand\n",6); */
  /* TODO: */
  /* exit(1); */
  r0 = combin(r0, r3, 0);
  r1 = ~r1;
  *r2 = (~r1) & *r2;
  goto eoprnd; 

exrsh:
  /* write(0,"exrsh\n",6); */
  r1 = -r1;
  if(r1 == 0){
    goto exlsh;
  }
  r1++;
  /* TODO */
  /* exit(1); */
  *r2 = ((*r2 >> 1) & 177) | (*r2 << 15);
  goto exlsh;
 
exlsh:
  /* write(0,"exlsh\n",6); */
  r0 = combin(r0, r3, 0);
  /* TODO */
  /* exit(1); */
  if(r1>0){
    *r2 = *r2 << r1;
  }else{
    *r2 = *r2 >> (-r1);
  }
  goto eoprnd; 

exmod:
  /* write(0,"exmod\n",6);*/
  r0 = combin(r0, r3, 0);
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

exnot:
  /* write(0,"exnot!!!!!\n",11); */
  r0 = combin(r0, r3, 0);
  r1 = ~r1;
  *r2 =+ r1;
  goto eoprnd;

excmbin:
  /* write(0,"excmbin\n",8); */
  *r3 = r0;
  goto eoprnd;

eoprnd:
  write(0,"eoprnd\n",7);
  sp = '+';
  goto advanc;

advanc:
  write(0,"advanc\n",7);
  /* advanc */ 
  r4 = readop_();
  /* printf("%d\n", r4); */
  /* cexprs(r2, r3, r4); */
  goto sbrtn;

finish:
  write(0,"finish\n",7);
  /* exit(0); */
  /*
  printf("---%d(opfound\n", opfound);
  */
  /* printf("fin cexprs (eof): r4:%x\n", r4); */
  return r4;
}

 /* void _combin(r0:in, r3:out, r5:in)
  *  value     : r0,r3  (r3 == pc)
  *  reference : r5
  */
int combin(r0, r3, r5) int r0; int *r3; int *r5;{
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
  }else if(*r5 != 0 && r0 == (*r3)){
    (*r3) = 1;
  }

  (*r3) = (*r3) | local1;

  return r0; 
}

