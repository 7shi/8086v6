/* translated from as29.s */

int defund;
char *unglob, *aout, faout;

_aexit();

_main()
{
    if (unglob) {
        /* globalize all undefineds (-g) */
        defund = 040;
    }
    if (!(signal(2, 1) & 1)) {
        signal(2, _aexit);
    }
    if ((faout = creat(aout, 0)) < 0) {
        _filerr(aout);
    }
    _go();
}
