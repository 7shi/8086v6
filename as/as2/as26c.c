/* translated from as26.s */

errore()
{
	error("e");
}

errora() 
{
	error("a");
}

checkrp(r4)
int r4;
{
	if(r4 == 051) {
		return readop();
	} 
	error(")");
	return r4;
}

