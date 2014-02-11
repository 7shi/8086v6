/* translated from as24.s */
int savop;
int ibufc;
int *ibufp;
int fin;
int inbuf[256];
char symtab[];
char usymtab[];

int
oset(r0, r1, r2)
{
	int *ptr;

	ptr = r1;
	r0 = r0 & 0777;
	r0 = r0 + r1;
	r0 = r0 + 6;

	*ptr = r0;
	ptr++;
	r0 = ptr;
	r0 = r0 + 01004;
	*ptr = r0;
	ptr++;
	*ptr = r2;
	ptr++;

	return ptr;
}

int
readop()
{
	int r4;
	int head;

	r4 = savop;
	if( r4 != 0 ){
		savop = 0;
		return r4;
	}

	getw1(&r4);
	if( r4 < 0200 ){
		return r4;
	}

	if( r4 < 04000 ){
		head = &symtab[0];
		r4 = r4 + (head - 01000);
		return r4;
	}
	head = &usymtab[0];
	r4 = r4 + (head - 04000);
	return r4;
}

int 
getw(r4)
int *r4;
{
	*r4 = savop;
	if( *r4 == 0 ){
		return getw1(r4);
	}
	savop = 0;
	return 0;
}

int
getw1(r4)
int *r4;
{
	int r0;

	ibufc--;
	if( ibufc > 0 ){
		goto label1;
	}

	r0 = read(fin,inbuf,512);
	if( r0 < 0 ){
		*r4 = 4;
		return 1;
	}

	r0 = r0 >> 1;
	ibufc = r0;
	if( r0 == 0 ){
		*r4 = 4;
		return 1;
	}
	ibufp = &inbuf[0];
label1:
	*r4 = *ibufp;
	ibufp++;
	return 0;
}

