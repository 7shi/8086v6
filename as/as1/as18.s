/
/

/ a8 -- pdp-11 assembler pass 1

.globl _chartab; _chartab: chartab:
	.byte -14,-14,-14,-14,-02,-14,-14,-14
	.byte -14,-22, -2,-14,-14,-22,-14,-14
	.byte -14,-14,-14,-14,-14,-14,-14,-14
	.byte -14,-14,-14,-14,-14,-14,-14,-14
	.byte -22,-20,-16,-14,-20,-20,-20,-12
	.byte -20,-20,-20,-20,-20,-20,056,-06
	.byte 060,061,062,063,064,065,066,067
	.byte 070,071,-20,-02,-00,-20,-14,-14
	.byte -14,101,102,103,104,105,106,107
	.byte 110,111,112,113,114,115,116,117
	.byte 120,121,122,123,124,125,126,127
	.byte 130,131,132,-20,-24,-20,-20,137
	.byte -14,141,142,143,144,145,146,147
	.byte 150,151,152,153,154,155,156,157
	.byte 160,161,162,163,164,165,166,167
	.byte 170,171,172,-14,-26,-14,176,-14

.data

.globl _namedone; _namedone: namedone:.byte 0
	.even
.globl _curfb; _curfb: curfb:
	-1;-1;-1;-1;-1;-1;-1;-1;-1;-1
.globl _obufp; _obufp: obufp:	outbuf
.globl _symend; _symend: symend:	usymtab

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
.globl _opfount; _opfount: opfound:.=.+2
.globl _savop; _savop: savop:	.=.+2
.globl _numval; _numval: numval:	.=.+2
.globl _nxtfb; _nxtfb: nxtfb:	.=.+4
.globl _usymtab; _usymtab: usymtab:.=.+36.
.globl _end; _end: end:
.text
