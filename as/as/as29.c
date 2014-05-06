/* translated from as29.s */

int symtab[];

int *_dotrel &symtab[1];
int *_dot    &symtab[2];
int *_dotdot &symtab[5];

int defund;
char *_atmp1, *_atmp2, *_atmp3, *aout, faout;

_aexit();

_main(argv1, argv2, argv3, argv4)
char *argv1, *argv2, *argv3, *argv4;
{
    if (argv4) {
        /* globalize all undefineds (-g) */
        defund = 040;
    }
    _atmp1 = argv1;
    _atmp2 = argv2;
    _atmp3 = argv3;
    if (!(signal(2, 1) & 1)) {
        signal(2, _aexit);
    }
    if ((faout = creat(aout, 0)) < 0) {
        _filerr(aout);
    }
    _go();
}
