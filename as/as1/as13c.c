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
	for (;;) {
		r4 = readop();
		if (!checkeos(r4)) {
			if (ifflg) {
				if (r4 > 0200) {
					if (*r4 == 021/*if*/)
						++ifflg;
					else if (*r4 == 022/*endif*/)
						--ifflg;
				}
				continue;
			}
			oldr4 = r4;
			r4 = readop();
			if (r4 == '=') {
				r4 = expres(readop(), &r2, &r3);
				r1 = oldr4;
				if (r1 < 0200)
					error("x");
				else if (r1 != &dotrel || (r3 & ~040) == dotrel) {
					*r1 =& ~037;
					r3 =& 37;
					if (!r3) r2 = 0;
					*r1 =| r3;
					(r1 + 2)->ival = r2;
				} else {
					error(".");
					dotrel = 2;
				}
			} else if (r4 == ':') {
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
				savop = r4;
				r4 = opline(oldr4);
			}
		}
		if (r4 == 4/*EOT*/) {
			if (ifflg) error("x");
			break;
		} else if (r4 == '\n') {
			++line;
		} else if (r4 != ';') {
			error("x");
			while (!checkeos(r4)) {
				r4 = readop();
			}
		}
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
