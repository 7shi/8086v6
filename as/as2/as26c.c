/* translated from as26.s */

checkrp(r4)
int r4;
{
	if(r4 == 051) {
		return readop();
	} 
	error(")");
	return r4;
}

checkreg(r1, r2, r3)
int r1;
int *r2;
int *r3;
{
	if((*r2 > 7) || ((*r3 >= 0) && (*r3 < 5))) {
		error("a");
		*r2 = *r3 = 0; 
		return;
	}
	/*
	if(r1 <= 1) {
		return;
	}
	*/
}
