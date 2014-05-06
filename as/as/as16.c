/* translated from as16.s */

struct Op { char type, num; int value; };

int savop;

/* checkrp()を汎用化（独自関数） */
checkop(ch)
{
    int op;
    if ((op = readop()) == ch) return 1;
    savop = op;
    return 0;
}

/* トークンがシンボルかどうかを判定（独自関数） */
issym(op)
{
    return op < 0 || 127 < op;
}
