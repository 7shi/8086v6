strncmp(s1, s2, n)
char *s1, *s2;
{
	int d;
	for (; n > 0; --n, ++s1, ++s2) {
		d = *s1 - *s2;
		if (d < 0) return -1;
		if (d > 0) return 1;
		if (!*s1) return 0;
	}
	return 0;
}

memcpy(d, s, n)
char *d, *s;
{
	for (; n > 0; --n, ++d, ++s) {
		*d = *s;
	}
}

memset(d, v, n)
char *d;
{
	for (; n > 0; --n, ++d) {
		*d = v;
	}
}

debug8(s, v)
char *s;
{
	int i;
	char buf[7];
	for (i = 0; s[i]; ++i);
	write(2, s, i);
	for (i = 0; i < 6; ++i) {
		buf[5 - i] = '0' + (v & 7);
		v =>> 3;
	}
	buf[6] = '\n';
	write(2, buf, 7);
}
