/* translated from as13.s */

struct opcode { char op0, op1; int op2; };

char *savop;
int ifflg;
int line;
int numval;
int dotrel;
int dot;
char fbfil;
struct opcode nxtfb;
char curfbr[];
int curfb[];

assem() {
	int r0, r1, r2, r3, r4, oldr4;
	for (;;) {
		r4 = readop();
		if (!checkeos(r4)) {
			if (ifflg) {
				if (r4 > 0200) {
					if (r4->op0 == 021/*if*/)
						++ifflg;
					else if (r4->op0 == 022/*endif*/)
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
					r3 =& 037;
					r1->op0 =& ~037;
					r1->op0 =| r3;
					r1->op2 = r3 ? r2 : 0;
				} else {
					error(".");
					dotrel = 2;
				}
			} else if (r4 == ':') {
				r4 = oldr4;
				if (r4 >= 0200) {
					if (r4->op0 & 037) error("m");
					r4->op0 =| dotrel;
					r4->op2 = dot;
				} else if (r4 == 1/*digit*/) {
					r0 = fbcheck(numval);
					curfbr[r0] = dotrel;
					curfb[r0] = dot;
					nxtfb.op0 = dotrel;
					nxtfb.op1 = r0 << 1;
					nxtfb.op2 = dot;
					write(fbfil, &nxtfb, 4);
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
