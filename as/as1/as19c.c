/* translated from as19.s */

/* for start() */
char pof;
char fbfil;
int unglob;
char nargs;
int curarg;
char atmp1[];
char atmp2[];

int aexit();

/*
 * void start (int argc, char* argv[])
 */
start(argc, argv) int argc; char *argv[];{
  int ret;

  ret = signal(2,1);
  if(ret & 1 == 0){
    signal(2, aexit);
  }

  if(argv[1][0] == '-'){
    argv++;
    argc--;
  }else{
    unglob = 0;
  }

  nargs  = argc;
  curarg = argv;

  pof = fcreat(atmp1);
  fbfil = fcreat(atmp2);
}

/* for setup() */
char symtab[];
char ebsymtab[];
char* hshsiz;
char hshtab[];

dump(){
  char* r1;
  for(r1 = hshtab;r1 < hshtab+hshsiz*2;r1++){
    if((r1 - hshtab)%16 == 0) printf("\n%04x:", r1);
    printf(" %2x", *r1);
  }
}

/*
 * void setup(void);
 */
setup(){
  char* r1;
  char* r3;
  char* r2;
  char* v1;
  char r4;

  char* *a;

  r1 = symtab;

  do{
    /* 1: */
    r3 = 0;
    r2 = 8;
    v1 = r1;

    /* 2: */
    /* char r4 */
    do{
      r4 = *(r1++);
      /* r4 == '\0' */
      if(r4 == 0){
        break;
      }

      /* 末尾2文字をハッシュテーブルのIdxの元とする */
      r3 = r3 + r4;
      r3 = (r3 << 8) + ((r3 >> 8) & 0377);
    }while(--r2);
  
    /* 2: */
    r2 = 0;

    /* r2 = r3 / hshsiz; /* div result   */
    /* r3 = r3 % hshsiz; /* div reminder */
    while(r3 >= hshsiz){
      r3 = r3 - hshsiz;
      r2++;
    }

    r2 = r2 << 1 + ((r3 >> 15) & 1);
    r3 = r3 << 1;
    r3 = r3 + hshtab;

    do{
      /* 4: */
      r3 = r3 - r2;
      if(hshtab >= r3){
        r3 = r3 + hshsiz * 2; /* r3 += 1553 * 2 */
      }
  
      /* 3: */
      r3 =- 2;
    }while(*r3 != 0);

    r1 = v1;
    a = r3;
    *a = r1;
    r1 = r1 + 12; /* シンボルテーブルを1行づつずらす */

  }while(r1 < ebsymtab);
}

/* setupの変数を書き直したもの */
setup2(){
  char* p_sym; /* r1          : current position of name in symboltbl */
  char* c_sym; /* optional var: current position of symboltbl*/

  char count;  /* r2 1st */
  char quot;   /* r2 2nd: quotient */

  char* key;   /* r3 1st */
  char* idx;   /* r3 2nd */
  char* *hash; /* r3 3rd */

  char ch;     /* r4 */

  p_sym = symtab;
  c_sym = symtab;

  do{
    /* 1: */
    key = 0;
    count = 8;
    /* c_sym = p_sym; */

    /* 2: */
    do{
      ch = *(p_sym++);
      if(ch == '\0'){
        break;
      }

      /* 末尾2文字をハッシュテーブルのkeyとする */
      key =+ ch;
      key = (key << 8) + ((key >> 8) & 0377);
    }while(--count);
  
    /* 2: */
    quot = 0;
    idx = key;

    /* 
     * div命令の置き換え, 32bit演算のため演算子'/'は使用できない 
     * div $hshsiz, r2
     * */
    while(idx >= hshsiz){
      idx =- hshsiz;
      quot++;
    }

    /* 
     * ashc命令の置き換え, 32bit演算のため演算子'<<'はそのままでは使用できない
     * ashc $1, r2 ---> quot(商):idx(剰余)
     * */
    /* 実際にはhshsizは1533.(0x611)なのでashcでキャリーは発生しないので
     * ここは単純に値を2倍にしているだけだと思われる */
    /* quot = quot << 1 + ((idx >> 15) & 1); */
    quot = quot << 1;
    idx = idx << 1;
    idx =+ hshtab;

    do{
      /* 4: */
      idx =- quot;
      if(hshtab >= idx){
        idx =+ hshsiz * 2;
      }
  
      /* 3: */
      /* 終端をオーバーフローしないように2[Byte]分減算する
       * 先頭をアンダーフローすることは無い（∵ ashcで2倍にしているから）*/
      idx =- 2;
    }while(*idx != 0);

    hash = idx;
    *hash = c_sym;
    p_sym = c_sym + 12; /* シンボルテーブルを1行づつずらす */
    c_sym = p_sym;

  }while(p_sym < ebsymtab);
}

