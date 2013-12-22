/
/

/ a8 -- pdp-11 assembler pass 1

_chartab: chartab:
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

_namedone: namedone:.byte 0
	.even
_curfb: curfb:
	-1;-1;-1;-1;-1;-1;-1;-1;-1;-1
_obufp: obufp:	outbuf
_symend: symend:	usymtab

.bss
_curfbf: curfbr:	.=.+10.
_savdot: savdot:	.=.+6
_bufscnt: bufcnt:	.=.+2
hshsiz = 1553.
_hshtab: hshtab:	.=2*hshsiz+.
_pof: pof:	.=.+1
_wordf: wordf:	.=.+1
_fin: fin:	.=.+1
_fbfil: fbfil:	.=.+1
_fileflg: fileflg:.=.+1
_errflg: errflg:	.=.+1
_ch: ch:	.=.+1
.even
_symbol: symbol:	.=.+8.
_obufc: obufc:	.=.+2
_outbuf: outbuf:	.=.+512.
_line: line:	.=.+2
_inbfcnt: inbfcnt:.=.+2
_ifflg: ifflg:	.=.+2
_inbfp: inbfp:	.=.+2
_nargs: nargs:	.=.+2
_curarg: curarg:	.=.+2
_opfount: opfound:.=.+2
_savop: savop:	.=.+2
_numval: numval:	.=.+2
_nxtfb: nxtfb:	.=.+4
_usymtab: usymtab:.=.+36.
_end: end:
.text
