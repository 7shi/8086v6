#
/* PDP-11 Assembler for the VAX Pass 0 */

#include "vars1.h"
#include <limits.h>

char a_tmp1[PATH_MAX] =	"/tmp/atm1_XXXXXX";
char a_tmp2[PATH_MAX] = "/tmp/atm2_XXXXXX";
char a_tmp3[PATH_MAX] = "/tmp/atm3_XXXXXX";

char iobuf[BUFSIZ];

char *symend;

short savdot[3];
struct symbol *hshtab[HSHSIZE];
FILE *pof, *fbfil;
char fileflg, errflg, ch;

struct symbol symbol;
int line;
int ifflg;
int nargs;
char **curarg;
uintptr_t saveop;
short numval;
struct symbol *usymtab;
char *endcore;
