/* translated from as15.s */

int savop, numval;
char ch, chartab[];

readop() {
	int r0, oldr0, r1, r4;
	if (r4 = savop) {
		savop = 0;
		return r4;
	}
	for (;;) {
		r4 = rch(); /* 0-127 */
		r1 = chartab[r4];
		if (r1 == -12 /* garb */)
			error("g");
		else if (r1 != -18)
			break;
	}
	switch (r1) {
	case -22: /* fixor | */
		r4 = 31;
		break;
	case -20: /* escp \ */
		switch (r4 = rch()) {
		case '/': r4 = '/'; break; /* \/ avoid comment */
		case '<': r4 = 29; break;
		case '>': r4 = 30; break;
		case '%': r4 = 31; break;
		}
		break;
	case -16: /* retread $%&... */
		break;
	case -14: /* dquote " */
		oldr0 = rsch(0);
		r0    = rsch(0);
		r0 =<< 8;
		r0 =| oldr0;
		r4 = 1;
		break;
	case -10: /* squote ' */
		r0 = rsch(0);
		r4 = 1;
		break;
	case -6: /* skip / comment */
		do {
			r4 = rch();
		} while (r4 != 4/*EOT*/ && r4 != '\n');
		break;
	case -2: /* retread */
		break;
	case 0: /* string < */
		putw('<');
		for (numval = 0; (r0 = rsch(1)) >= 0; ++numval)
			putw(r0 | 256);
		putw(-1);
		return '<';
	default: /* -18, -12, 自然数（ASCIIのまま） */
		ch = r4;
		if ('0' <= r1 && r1 <= '9') {
			r4 = number(&r0);
			break;
		}
		return rname();
	}
	putw(r4);
	if (r4 == 1) {
		/* default(数字のとき), squote, dquote */
		putw(numval = r0);
	}
	return r4;
}

rsch(isstr)
{
	int r0;
	r0 = rch();
	if (r0 == 4/*EOT*/ || r0 == '\n') {
		error("<");
		aexit();
	} else if (r0 == '\\') {
		switch (r0 = rch()) {
		case 'n': return 10;
		case 't': return  9;
		case 'e': return  4;
		case '0': return  0;
		case 'r': return 13;
		case 'a': return  6;
		case 'p': return 27;
		}
		return r0;
	}
	if (isstr && r0 == '>') return -1;
	return r0;
}
