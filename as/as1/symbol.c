int hshsiz;
int hshtab[];

/* シンボルテーブルを検索（独自関数） */
char **
srchsym(key, name)
char *name;
{
	int quot;
	char ch, **idx;

	quot = ldiv(0, key, hshsiz);
	idx = hshtab + lrem(0, key, hshsiz);
	do{
		idx =- quot + 1;
		if(idx < hshtab) idx =+ hshsiz;
	} while (*idx && strncmp(*idx, name, 8));
	return idx;
}

char *memend, *symend;

struct {
	char symname[8];
	int symtype, symval;
};

char *
addsym(name, type, val)
char *name;
{
	char *sym;
	sym = symend;
	symend =+ 12;
	if (symend > memend) {
		sbrk(512);
		memend =+ 512;
	}

	memset(sym, 0, 8);
	strncpy(sym, name, 8);
	sym->symtype = type;
	sym->symval  = val;
	return sym;
}
