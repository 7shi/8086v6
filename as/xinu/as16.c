/* PDP-11 Assembler for the VAX Pass 0 */

#include "vars1.h"
#include "stypes.h"

int adrinc;

intptr_t address(intptr_t);
intptr_t getx(intptr_t);
intptr_t alp();
intptr_t amin();
intptr_t adoll();
intptr_t astar();
intptr_t checkrp(intptr_t);

intptr_t
opline(op)
intptr_t op;
{
	char optype;
	int offset, temp;

	if(op > 0 && op < 0200)
		if(op == '<') goto ascii;
		else goto xpr;
	optype = *((char *)op);
	if(optype == TREG || optype <= TBSS || optype > TJCOND )
		goto xpr;
	op = readop();
	switch(optype) {
	    case TFLDST: case TJSR: case TMOVF: case TDBLOP:
	    case TFLREG: case TMUL:
		op = address(op);
		if(op != ',') {
			error('a');
			return(op);
		}
		op = readop();

	    case TSINGLE:
		op = address(op);
		DOT += 2;
		return(op);

	    case TSOB:
		op = expres(op);
		if(op != ',') error('a');
		op = readop();
		break;

	    case TCBYTE:
		for(;;op = readop()) {
			op = expres(op);
			DOT++;
			if(op != ',') break;
		}
		return(op);

	    case TCSTR:
	ascii:
		DOT += numval;
		return(readop());

	    case TCEVEN:
		DOT++;
		DOT &= ~1;
		return(op);

	    case TCIF:
		op = expres(op);
		if(etype == 0) error('u');
		if(!eval) ifflg++;

	    case TCENDIF:
		return(op);

	    case TCGLOBL:
		for(;;op = readop()) {
			if((uintptr_t)op < 0200) return(op);
			((struct sinfo *)op)->s_type |= 040;
			if((op = readop()) != ',') return(op);
		}
		/* NOTREACHED */

	    case TREG: case TETEXT: case TEDATA:
	    case TBR: case TRTS: case TSYS:
		break;

	    case TCTEXT: case TCDATA: case TCBSS:
		savdot[DOTREL-2] = DOT;
		DOT = savdot[optype-TCTEXT];
		DOTREL = optype - TCTEXT + 2;
		return(op);

	    case TCCOMM:
		if((uintptr_t)op < 0200) {
		    comerr:
			error('x');
			return(op);
		}
		((struct sinfo *)op)->s_type |= 040;
		if((op = readop()) != ',') goto comerr;
		return(expres(readop()));

	    case TJBR: case TJCOND:
		temp = (optype == TJBR ? 04 : 06);
		op = expres(op);
		if(etype == DOTREL) {
			offset = eval - DOT;
			if(offset < 0 && offset >= -0376) temp = 2;
		}
		DOT += temp;
		return(op);
	}
xpr:
	op = expres(op);
	DOT += 2;
	return(op);
}	

intptr_t
address(op)
intptr_t op;
{
	switch(op) {
	    case '(':
		return(alp());

	    case '-':
		return(amin());

	    case '$':
		return(adoll());

	    case '*':
		return(astar());

	    default:
		return(getx(op));
	}
}

intptr_t
getx(op)
intptr_t op;
{
	op = expres(op);
	if(op == '(') {
		op = expres(readop());
		op = checkrp(op);
		checkreg();
		DOT += 2;
		adrinc = 0;
		return(op);
	}
	if(etype == TREG) checkreg();
	else DOT += 2;
	adrinc = 0;
	return(op);
}

intptr_t
alp() {
	intptr_t op;

	op = expres(readop());
	op = checkrp(op);
	checkreg();
	if(op == '+') {
		op = readop();
		adrinc = 0;
	} else adrinc = 2;
	return(op);
}

intptr_t
amin() {
	intptr_t op;

	if( (op = readop()) != '(') {
		saveop = op;
		op = '-';
		return(getx(op));
	}
	op = expres(readop());
	op = checkrp(op);
	checkreg();
	adrinc = 0;
	return(op);
}

intptr_t
adoll() {
	intptr_t op;

	op = expres(readop());
	DOT += 2;
	adrinc = 0;
	return(op);
}

intptr_t
astar() {
	intptr_t op;

	if( (op = readop()) == '*') error('*');
	op = address(op);
	DOT += adrinc;
	return(op);
}


checkreg() {
	if(eval > 7 || (etype != TABS && etype <= TBSS)) error('a');
}

intptr_t
checkrp(op)
intptr_t op;
{
	if(op != ')') {
		error(')');
		return(op);
	}
	return(readop());
}
