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

/* シンボルテーブルを検索（独自関数） */
char **srchsym(key, name) char *name; {
  int quot;
  char ch, **idx;

  quot = ldiv(0, key, hshsiz);
  idx = hshtab + lrem(0, key, hshsiz);
  do{
    idx =- quot + 1;
    if(idx < hshtab) idx =+ hshsiz;
  }while(*idx && strncmp(*idx, name, 8));
  return idx;
}

/*
 * void setup(void);
 */
setup(){
  char ch, *p;
  int key, i;

  for(p = symtab; p < ebsymtab; p =+ 12){
    /* バイト反転しながら文字を加算してハッシュを算出 */
    for(key = 0, i = 0; i < 8 && (ch = p[i]); ++i){
      key =+ ch;
      key = (key << 8) + ((key >> 8) & 0377);
    }

    *srchsym(key, p) = p;
  }
}
