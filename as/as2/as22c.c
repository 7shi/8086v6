/* translated from as22.s */

int outmod;
char argb[];
int line[];

error(r5)
char r5;
{
	int i, data;
	char *buf, *p;
	
	buf = "f xxxx\n";

	/* outmodを666にする */
	outmod = 0666;

	/* argbの内容を書き出し，終了を0を書き込む */
	for(i = 0; argb[i] != 0; i++);
	write(1, argb, i);
	for(i = 0; argb[i] != 0; i++) argb[i] = 0;


	data = line[0];
	buf[0] = r5;

	/* line[0]の内容を10進数で表示する */
	p = &buf[6];
	for(i = 0; i < 4; i++) {
		*(--p) = '0' + (data % 10);
		data =/ 10;
	}

	write(1, buf, 7);

	return;
}


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

