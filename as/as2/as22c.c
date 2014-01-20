/* translated from as22.s */

betwen(r0, r5)
int r0;
int r5[];
{
	if(r0 < r5[0]) {
		return 0;
	} else if(r5[1] < r0) {
		return 0;
	}
	return 1;
}

