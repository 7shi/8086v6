int hshsiz;
int hshtab[];
char *usymtab, *symend, *memend;

/* 以下は独自に追加した関数 */

/* シンボルテーブルを検索 */
char **
symget(key, name)
char *name;
{
	int quot, *idx;
	quot = ldiv(0, key, hshsiz);
	idx = hshtab + lrem(0, key, hshsiz);
	do {
		idx =- quot + 1;
		if(idx < hshtab) idx =+ hshsiz;
	} while (*idx && symcmp(*idx, name));
	return idx;
}

struct { int ival; };

/* シンボル名をチェック */
symcmp(idx, name)
{
	return strncmp(idx < usymtab ? idx->ival : idx, name, 8);
}
