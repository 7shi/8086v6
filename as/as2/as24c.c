/* translated from as24.s */
int ps_psw 0;
int savop;
int ibufc;
int *ibufp;
int fin;
int inbuf[256];

int 
getw()
{
	int r4;

	r4 = savop;
	if( r4 == 0 ){
		r4 = getw1();
		return r4;
	}
	savop = 0;

	return r4;
}

int
getw1()
{
	int r0;
	int r4;

	ibufc--;
	if( ibufc > 0 ){
		goto label1;
	}

	r0 = read(fin,inbuf,512);
	if( r0 < 0 ){
		r4 = 4;
		/* sev instruction */
		ps_psw = ps_psw | 2;
		return r4;
	}

	r0 = r0 >> 1;
	ibufc = r0;
	if( r0 == 0 ){
		r4 = 4;
		/* sev instruction */
		ps_psw = ps_psw | 2;
		return r4;
	}
	ibufp = &inbuf[0];
label1:
	r4 = *ibufp;
	ibufp++;
	return r4;
}

