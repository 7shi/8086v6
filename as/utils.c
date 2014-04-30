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

char *
strncpy(s1, s2, n)
char *s1, *s2;
{
    char *ret;
    ret = s1;
    for (; n > 0; --n, ++s1, ++s2) {
        *s1 = *s2;
        if (!*s2) break;
    }
    memset(s1, 0, n);
    return ret;
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
{
    int i;
    char buf[7];
    if (s < 0 || 127 <= s) {
        write(2, s, strlen(s));
    } else if (32 <= s) {
        s =| ' ' << 8;
        write(2, &s, 2);
    }
    for (i = 0; i < 6; ++i) {
        buf[5 - i] = '0' + (v & (i < 5 ? 7 : 1));
        v =>> 3;
    }
    buf[6] = '\n';
    write(2, buf, 7);
}

debug16(s, v)
{
    int i;
    char buf[5], *hexstr;
    hexstr = "0123456789abcdef";
    if (s < 0 || 127 <= s) {
        write(2, s, strlen(s));
    } else if (32 <= s) {
        s =| ' ' << 8;
        write(2, &s, 2);
    }
    for (i = 0; i < 4; ++i) {
        buf[3 - i] = hexstr[v & 15];
        v =>> 4;
    }
    buf[4] = '\n';
    write(2, buf, 5);
}

min(a, b) { return a < b ? a : b; }
max(a, b) { return a > b ? a : b; }
