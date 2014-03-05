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
