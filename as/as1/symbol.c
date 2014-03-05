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
