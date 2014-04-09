/* translated from as13.s */

char *savop, fbfil, curfbr[];
int ifflg, line, numval, curfb[];
int *dotrel, *dot;
struct { int type, val; };

assem() {
	int num, r3, op, op2;
	for (;;) {
		op = readop();
		if (!checkeos(op)) {
			if (ifflg) {
				if (op >= 128) {
					if (op->type == 17/*if*/) {
						++ifflg;
					} else if (op->type == 18/*endif*/) {
						--ifflg;
					}
				}
				continue;
			}
			op2 = readop();
			if (op2 == '=') {
				num = expres(readop(), &r3);
				if (op < 128) {
					error("x");
				} else if (op != dotrel || (r3 & ~32) == *dotrel) {
					r3 =& 31;
					op->type = (op->type & ~31) | r3;
					op->val = r3 ? num : 0;
				} else {
					error(".");
					*dotrel = 2;
				}
				op = readop();
			} else if (op2 == ':') {
				if (op >= 128) {
					if (op->type & 31) error("m");
					op->type =| *dotrel;
					op->val = *dot;
				} else if (op == 1/*digit*/) {
					num = fbcheck(numval);
					curfbr[num] = *dotrel;
					curfb[num] = *dot;
					num =<< 1;
					write(fbfil, dotrel, 1);
					write(fbfil, &num, 1);
					write(fbfil, dot, 2);
				} else {
					error("x");
				}
				continue;
			} else {
				savop = op2;
				op = opline(op);
			}
		}
		if (op == 4/*EOT*/) {
			if (ifflg) error("x");
			break;
		} else if (op == '\n') {
			++line;
		} else if (op != ';') {
			error("x");
			while (!checkeos(op)) {
				op = readop();
			}
		}
	}
}

fbcheck(n) {
	if (n <= 9) return n;
	error("f");
	return 0;
}

checkeos(op) {
	return op == '\n' || op == ';' || op == 4/*EOT*/;
}
