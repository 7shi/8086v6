/* translated from as15.s */

int savop;
char chartab[];
char ch;
int numval;

debug8(s, v)
char *s; {
	int i;
	char buf[7];
	for (i = 0; s[i]; ++i);
	write(2, s, i);
	for (i = 0; i < 6; ++i) {
		buf[5 - i] = '0' + (v & 7);
		v =<< 3;
	}
	buf[6] = '\n';
	write(2, buf, 7);
}

readop() {
	int r0, oldr0, r1, r4;
	if (r4 = savop) {
		savop = 0;
		return r4;
	}
	for (;;) {
		r1 = chartab[r4 = rch()];
		if (r1 == -014 /* garb */)
			error("g");
		else if (r1 != -022)
			break;
	}
	switch (r1) {
	case -026: /* fixor */
		r4 = 037;
		break;
	case -024: /* escp */
		switch (r4 = rch()) {
		case '/': r4 = '/'; break;
		case '<': r4 = 035; break;
		case '>': r4 = 036; break;
		case '%': r4 = 037; break;
		}
		break;
	case -020: /* retread */
		break;
	case -016: /* dquote */
		rsch(&oldr0);
		rsch(&r0);
		r0 =<< 8;
		r0 =| oldr0;
		r4 = 1;
		break;
	case -012: /* squote */
		rsch(&r0);
		r4 = 1;
		break;
	case -006: /* skip */
		do {
			r4 = rch();
		} while (r4 != 4/*EOT*/ && r4 != '\n');
		break;
	case -004: /* rdnum */
		r4 = number(&r0);
		break;
	case -002: /* retread */
		break;
	case  000: /* string */
		putw('<');
		for (numval = 0; !rsch(&r0); ++numval)
			putw(r0 | 0400);
		putw(-1);
		return '<';
	case -010: /* rdname */
	default:
		ch = r4;
		if ('0' <= r1 && r1 <= '9') {
			r4 = number(&r0);
			break;
		}
		r0 = rname0(r4);
		debug8("rname0: ", r0);
		return r0;
	}
	putw(r4);
	if (r4 == 1) {
		/* rdname(数字のとき), rdnum, squote, dquote */
		putw(numval = r0);
	}
	return r4;
}

rsch(r0)
int *r0;
{
	*r0 = rch();
	if (*r0 == 4/*EOT*/ || *r0 == '\n') {
		error("<");
		aexit();
	} else if (*r0 == '\\') {
		switch (*r0 = rch()) {
		case 'n': *r0 = 012; break;
		case 't': *r0 = 011; break;
		case 'e': *r0 = 004; break;
		case '0': *r0 = 000; break;
		case 'r': *r0 = 015; break;
		case 'a': *r0 = 006; break;
		case 'p': *r0 = 033; break;
		}
		return 0;
	}
	return *r0 == '>';
}
