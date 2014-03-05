/
/

/ a8 -- pdp-11 assembler pass 1

.data

.globl _curfb; _curfb: curfb:
	-1;-1;-1;-1;-1;-1;-1;-1;-1;-1
.globl _obufp; _obufp: obufp:	outbuf

.bss
.globl _curfbr; _curfbr: curfbr:	.=.+10.
.globl _savdot; _savdot: savdot:	.=.+6
.globl _bufscnt; _bufscnt: bufcnt:	.=.+2
hshsiz = 1553.
.globl _hshtab; _hshtab: hshtab:	.=2*hshsiz+.
.globl _pof; _pof: pof:	.=.+1
.globl _wordf; _wordf: wordf:	.=.+1
.globl _fin; _fin: fin:	.=.+1
.globl _fbfil; _fbfil: fbfil:	.=.+1
.globl _fileflg; _fileflg: fileflg:.=.+1
.globl _errflg; _errflg: errflg:	.=.+1
.globl _ch; _ch: ch:	.=.+1
.even
.globl _symbol; _symbol: symbol:	.=.+8.
.globl _obufc; _obufc: obufc:	.=.+2
.globl _outbuf; _outbuf: outbuf:	.=.+512.
.globl _line; _line: line:	.=.+2
.globl _inbfcnt; _inbfcnt: inbfcnt:.=.+2
.globl _ifflg; _ifflg: ifflg:	.=.+2
.globl _inbfp; _inbfp: inbfp:	.=.+2
.globl _nargs; _nargs: nargs:	.=.+2
.globl _curarg; _curarg: curarg:	.=.+2
.globl _opfound; _opfound: opfound:.=.+2
.globl _savop; _savop: savop:	.=.+2
.globl _numval; _numval: numval:	.=.+2
.globl _nxtfb; _nxtfb: nxtfb:	.=.+4
.text
