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
  char* p_sym; /* r1 current position of name in symboltbl */
  char quot;   /* r2 quotient */
  char* key;   /* r3 1st */
  char* *idx;  /* r3 2nd */
  char ch;     /* r4 */
  int i;

  for(p_sym = symtab; p_sym < ebsymtab; p_sym =+ 12){
    /* 1: */
    key = 0;

    /* 2: バイト反転しながら文字を加算してハッシュを算出 */
    for(i = 0; i < 8 && (ch = p_sym[i]); ++i){
      key =+ ch;
      key = (key << 8) + ((key >> 8) & 0377);
    }
  
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

    *idx = p_sym;
  }
}
