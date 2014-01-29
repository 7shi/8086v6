/* translated from as24.s */
int savop;
int ibufc;
int *ibufp;
int fin;
int inbuf[256];

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

