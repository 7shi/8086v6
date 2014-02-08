/* translated from as13.s
assem: as11.s, as13.s
ealoop: as13.s
assem1: as13.s
fbcheck: as13.s, as14.s
checkeos: as13.s
*/

char *savop;
int ifflg;
int line;
int numval;
int dotrel;
int dot;
char fbfil;
char nxtfb[];
char curfbr[];
int curfb[];

struct { int ival; };

assem() {
	int r0;
	char *r1;
	int r2;
	int r3;
	char *r4;
	char *oldr4;
  int* tmp;



	for (;;) {
		r4 = readop_();

		if (!checkeos(r4)) { /* !(end of line) */
			if (ifflg) {
				if (r4 > 0200) { /* out of key-to-types */
					if (*r4 == 021/*if*/)
						++ifflg;
					else if (*r4 == 022/*endif*/)
						--ifflg;
				}
				continue;
			}
			oldr4 = r4;
			r4 = readop_();
/*
			r4 = readop_();
			r4 = readop_();
			r4 = readop_();
			r4 = readop_();
			r4 = readop_(); ':'
      printf("---%c(%x)\n", r4, r4);
*/
			if (r4 == '=') {

        write(0,"-->expres\n", 10);
         
        tmp = readop_();
				r4 = expres(tmp, &r2, &r3);

/*
        printf("---:\n");
*/
/*
        r4 = expres(readop_(), &r2, &r3);
*/
				r1 = oldr4;
				if (r1 < 0200) {
write(0,"-->error-0200\n", 14);
					error("x");
				} else if (r1 != &dotrel || (r3 & ~040) == dotrel) {
write(0,"-->dotrel\n", 10);
          /*
          printf("-->success r4:%x r2:%x r3:%x\n", r4, r2, r3);
          */
					*r1 =& ~037;
					r3 =& 37;
					if (!r3) r2 = 0;
					*r1 =| r3;
					(r1 + 2)->ival = r2;
				} else {
write(0,"-->error-\n", 10);
					error(".");
					dotrel = 2;
				}
			} else if (r4 == ':') {
write(0,"-->   :\n", 8);
				r4 = oldr4;
				if (r4 >= 0200) {
					if (*r4 & 037) error("m");
					*r4 =| dotrel;
					(r4 + 2)->ival = dot;
				} else if (r4 == 1/*digit*/) {
					r0 = fbcheck(numval);
					curfbr[r0] = dotrel;
					curfb[r0] = dot;
					nxtfb[0] = dotrel;
					nxtfb[1] = r0 << 1;
					(nxtfb + 2)->ival = dot;
					write(fbfil, nxtfb, 4);
				} else
					error("x");
				continue;
			} else {
write(0,"-->opline\n",10);
				savop = r4;
				r4 = opline(oldr4);
write(0,"-->opline-end\n",14);
			}
		}
    /* 
    printf("result r4:%c(%x)\n", r4, r4);
    */
		if (r4 == 4/*EOT*/) {
			if (ifflg) error("x");
			break;
		} else if (r4 == '\n') {
			++line;
		} else if (r4 != ';') {
write(0,"-->errorx\n",10);
			error("x");
			while (!checkeos(r4)) {
				r4 = readop_();
			}
		}
write(0,"-->loop end\n", 12);
	}
}

fbcheck(r0) {
	if (r0 <= 9) return r0;
	error("f");
	return 0;
}

checkeos(r4) {
	return r4 == '\n' || r4 == ';' || r4 == 4/*EOT*/;
}
