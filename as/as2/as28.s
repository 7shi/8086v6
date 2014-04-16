/
/

/ as8 -- PDP-11 assembler pass 2

.globl _qnl; _qnl: qnl:	<?\n>
.globl _aout; _aout: a.out:	<a.out\0>

.even
.globl _aoutp; _aoutp: a.outp:	a.out

	.data
.globl _atmp1; _atmp1: a.tmp1:	0
.globl _atmp2; _atmp2: a.tmp2:	0
.globl _atmp3; _atmp3: a.tmp3:	0

.globl _tseekp; _tseekp: tseekp:	txtseek
.globl _rseekp; _rseekp: rseekp:	trelseek

.globl _txtmagic; _txtmagic: txtmagic:
	br	.+20
.globl _txtsiz; _txtsiz: txtsiz:	.=.+2
.globl _datsiz; _datsiz: datsiz:	.=.+2
.globl _bsssiz; _bsssiz: bsssiz:	.=.+2
.globl _symsiz; _symsiz: symsiz:	.=.+2
.globl _stksiz; _stksiz: stksiz:	.=.+2
.globl _exorig; _exorig: exorig:	.=.+2
	.=.+2

.globl _txtseek; _txtseek: txtseek: 20
.globl _datseek; _datseek: datseek:.=.+2
	.=.+2
.globl _trelseek; _trelseek: trelseek:.=.+2
.globl _drelseek; _drelseek: drelseek:.=.+2
	.=.+2
.globl _symseek; _symseek: symseek:.=.+2
.globl _brlen; _brlen: brlen	= 1024.; brlen

.bss

.globl _brtab; _brtab: brtab:	.=.+[brlen\/8.]
.globl _brtabp; _brtabp: brtabp:	.=.+2
.globl _brdelt; _brdelt: brdelt:	.=.+2
.globl _fbbufp; _fbbufp: fbbufp:	.=.+2
.globl _defund; _defund: defund:	.=.+2
.globl _savdot; _savdot: savdot:	.=.+6
.globl _datbase; _datbase: datbase:.=.+2
.globl _bssbase; _bssbase: bssbase:.=.+2
.globl _fbfil; _fbfil: fbfil:	.=.+2
.globl _fin; _fin: fin:	.=.+2
.globl _ibufc; _ibufc: ibufc:	.=.+2
.globl _txtfil; _txtfil: txtfil:	.=.+2
.globl _symf; _symf: symf:	.=.+2
.globl _adrbuf; _adrbuf: adrbuf:	.=.+12.
.globl _xsymbol; _xsymbol: xsymbol:.=.+2
.globl _fout; _fout: fout:	.=.+2
.globl _ch; _ch: ch:	.=.+2
.globl _wordf; _wordf: wordf:	.=.+2
.globl _argb; _argb: argb:	.=.+22.
.globl _line; _line: line:	.=.+2
.globl _savop; _savop: savop:	.=.+2
.globl _curfb; _curfb: curfb:	.=.+20.
.globl _nxtfb; _nxtfb: nxtfb:	.=.+20.
.globl _numval; _numval: numval:	.=.+2
.globl _maxtyp; _maxtyp: maxtyp:	.=.+2
.globl _relfil; _relfil: relfil:	.=.+2
.globl _ibufp; _ibufp: ibufp:	.=.+2
.globl _txtp; _txtp: txtp:	.=.+6+512.
.globl _relp; _relp: relp:	.=.+6+512.
.globl _swapf; _swapf: swapf:	.=.+2
.globl _rlimit; _rlimit: rlimit:	.=.+2
.globl _passno; _passno: passno:	.=.+2
.globl _endtable; _endtable: endtable:.=.+2
.globl _usymtab; _usymtab: usymtab:.=.+2.
