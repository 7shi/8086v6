/* translated from as24.s */

oset(r0, r5)
{
    int *r1, next;
    r1 = r5;
    next = r5 + 6;
    /* next slot */
    r1[0] = next + (r0 & 0777);
    /* buf max */
    r1[1] = next + 01000;
    /* seek addr */
    r1[2] = r0;
}

putw(r0, r5)
{
    int **r2;
    r2 = r5;
    if (r2[0] >= r2[1]) {
        /* buf max */
        flush(r2);
    }
    *r2[0] = r0;
    ++r2[0];
}

int fout;

flush(r5)
{
    int r1, *r2, next;
    r2 = r5;
    next = r5 + 6;
    r1 = r2[2]; /* seek address */
    seek(fout, r1, 0);
    r2[2] = (r1 | 0777) + 1; /* new seek addr */
    r1 = next + (r1 & 0777); /* write address */
    write(fout, r1, r2[0] - r1);
    r2[0] = next; /* new next slot */
}

int savop;
int ibufc;
int *ibufp;
int fin;
int inbuf[256];
char symtab[];
char usymtab[];

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

