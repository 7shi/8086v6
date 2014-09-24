#
/* PDP-11 Assembler for the VAX Pass 0 */

#include "vars1.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define	PASS2	"../xinu/as2"

char fpass2[] = PASS2;
char globfl[] = "-\0";
char outfl[] = "-o";
char outfile[] = "a.out";

const char *argv2[] = {
	fpass2,
	globfl,
	outfl,
	outfile,
	a_tmp1,
	a_tmp2,
	a_tmp3,
	NULL };

go() {
	FILE *fd;

	assem();
	if (fclose(pof) == EOF)
		wrterr("can't close %s", a_tmp1);
	if (fclose(fbfil) == EOF)
		wrterr("can't close %s", a_tmp2);
	if (errflg)
		aexit();
	if ((fd = fcreat(a_tmp3)) == NULL)
		wrterr("can't create %s", a_tmp3);
	/* setbuf(fd, _sobuf); */
	if (symend != (char *)usymtab)
		if (fwrite((char *)usymtab, symend-(char *)usymtab, 1, fd) != 1)
			wrterr("can't write on %s", a_tmp3);
	if (fclose(fd) == EOF)
		wrterr("can't close %s", a_tmp3);
	execv(fpass2, argv2);
	fprintf(stderr, "%s?\n", fpass2);
}

void
saexit(_) {
	aexit();
}

aexit() {
	unlink(a_tmp1);
	unlink(a_tmp2);
	unlink(a_tmp3);
	exit(3);
}

FILE *
fcreat(name) char *name; {
	int fd;

	fd = mkstemp(name);
	if(fd == -1) {
		fprintf(stderr, "%s?\n", name);
		exit(3);
	}
	return(fdopen(fd, "wb"));
}

/* VARARGS1 */
wrterr(s, n)
char *s, *n;
{
	fprintf(stderr, "as: error on temp file: ");
	fprintf(stderr, s, n);
	fprintf(stderr, "\n");
	aexit();
}
