#include <string.h>
#include <stdint.h>

struct Sym { char type, num; short value; };
extern struct Sym curfbr[], *curfb[], *nxtfb[], *fbbufp;

union Op { intptr_t op; struct Sym *sym; };
extern union Op savop, readop();

extern short *dotrel, *dot;
extern int ifflg, line, numval, passno;
extern char fbfil, argb[];

extern void expres(struct Sym *, union Op);
extern void opline(union Op);

assem() {
    union Op op, op2;
    int i;
    short w;
    for (;;) {
        op = readop();
        if (op.op == 5) {
            /* file name */
            line = 1;
            memset(argb, 0, 22);
            for (i = 0;; ++i) {
                w = agetw();
                if (w < 0) break;
                if (i < 21) argb[i] = w;
            }
            continue;
        } else if (!checkeos(op)) {
            if (ifflg) {
                if (issym(op)) {
                    if (op.sym->type == 17/*.if*/) {
                        ++ifflg;
                    } else if (op.sym->type == 18/*.endif*/) {
                        --ifflg;
                    }
                }
                continue;
            }
            op2 = readop();
            if (op2.op == '=') {
                let(op);
            } else if (op2.op == ':') {
                label(op);
                continue;
            } else {
                savop = op2;
                opline(op);
            }
            op = readop();
        }
        if (op.op == 4/*EOT*/) {
            if (ifflg) error("x");
            break;
        } else if (op.op == '\n') {
            ++line;
        } else if (op.op != ';') {
            error("x");
            while (!checkeos(op)) {
                op = readop();
            }
        }
    }
}

let(op)
union Op op;
{
    struct Sym x;
    int i;
    expres(&x, readop());
    if (!issym(op)) {
        error("x");
    } else if (&op.sym->value == dot) { /* test for dot */
        x.type &= 31;
        if (x.type != *dotrel) {
            /* can't change relocation */
            error(".");
            if (passno == 0) *dotrel = 2;
        } else {
            if (passno == 0) {
                op.sym->type = (op.sym->type & 32) | x.type;
                op.sym->value = x.type ? x.value : 0;
            } else {
                if (x.type == 4) { /* bss */
                    *dot = x.value;
                } else if (*dot <= x.value) {
                    for (i = *dot; i < x.value; ++i) {
                        outb(1, 0);
                    }
                } else {
                    error(".");
                }
            }
        }
    } else {
        if (x.type == 32) error("r");
        x.type &= 31;
        if (x.type == 0) x.value = 0;
        op.sym->type &= 32;
        op.sym->type |= x.type;
        op.sym->value = x.value;
    }
}

label(op)
union Op op;
{
    struct Sym *fb;
    int t, num;
    if (issym(op)) {
        t = op.sym->type & 31;
        if (passno < 2) {
            if (t == 27 || t == 28) {
                op.sym->type &= 32;
            } else if (t) {
                error("m");
            }
            op.sym->type |= *dotrel;
            op.sym->value = *dot;
        } else {
            if (op.sym->value != *dot) error("p");
        }
    } else if (op.op == 1/*digit*/) {
        if (passno == 0) {
            num = fbcheck(numval);
            fb = &curfbr[num];
            fb->type  = *dotrel;
            fb->num   = num;
            fb->value = *dot;
            write(fbfil, fb, sizeof(*fb));
        } else {
            fbadv(numval);
            fb = curfb[numval];
            fb->type  = *dotrel;
            fb->value = *dot;
        }
    } else {
        error("x");
    }
}

fbadv(num)
{
    struct Sym *fb;
    fb = curfb[num] = nxtfb[num];
    if (!fb) fb = fbbufp - 1;
    do {
        ++fb;
    } while (fb->type >= 0 && fb->num != num);
    nxtfb[num] = fb;
}

fbcheck(n) {
    if (n <= 9) return n;
    error("f");
    return 0;
}

checkeos(op)
union Op op;
{
    return op.op == '\n' || op.op == ';' || op.op == 4/*EOT*/;
}
