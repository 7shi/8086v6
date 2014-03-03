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
 * void main (int argc, char* argv[])
 */
main(argc, argv) int argc; char *argv[];{
  int ret;

  ret = signal(2,1);
  if (ret & 1 == 0) {
    signal(2, aexit);
  }

  if (argv[1][0] == '-') {
    argv++;
    argc--;
  } else {
    unglob = 0;
  }

  nargs  = argc;
  curarg = argv;

  pof = fcreat(atmp1);
  fbfil = fcreat(atmp2);

  setup();
  go();
}

/* for setup() */
char symtab[];
char ebsymtab[];
int hshsiz;
int hshtab[];

/*
 * void setup(void);
 */
setup(){
  char* r1;
  int r2, r3;
  char* v1;
  char r4;
  char* *r3p;

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
    r2 = ldiv(0, r3, hshsiz);
    r3p = hshtab + lrem(0, r3, hshsiz);

    do{
      /* 4: */
      r3p =- r2;
      if(hshtab >= r3p){
        r3p =+ hshsiz; /* r3 += 1553 * 2 */
      }
  
      /* 3: */
      --r3p;
    }while(*r3p);

    r1 = v1;
    *r3p = r1;
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
  char* *idx;  /* r3 2nd */

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
    quot = ldiv(0, key, hshsiz);
    idx = hshtab + lrem(0, key, hshsiz);

    do{
      /* 4: */
      idx =- quot;
      if(hshtab >= idx){
        idx =+ hshsiz;
      }
  
      /* 3: */
      /* 終端をオーバーフローしないように2[Byte]分減算する
       * 先頭をアンダーフローすることは無い（∵ ashcで2倍にしているから）*/
      --idx;
    }while(*idx);

    *idx = c_sym;
    p_sym = c_sym + 12; /* シンボルテーブルを1行づつずらす */
    c_sym = p_sym;

  }while(p_sym < ebsymtab);
}

