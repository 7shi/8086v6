/* translated from as15.s */

int savop, numval, passno;
char ch, chartab[], *txtp[];

readop() {
    int c, num, type, ret;
    if (savop) {
        ret = savop;
        savop = 0;
        return ret;
    } else if (passno) {
        ret = getw();
        if (ret == 1) numval = getw();
        return ret;
    }
    for (;;) {
        c = rch(); /* 0-127 */
        type = chartab[c];
        if (type == -12 /* garb: #>?@`{} etc */) {
            error("g");
        } else if (type != -18 /* '\t', '\r', ' ' */) {
            break;
        }
    }
    switch (type) {
    case -22: /* fixor: | */
        ret = 31;
        break;
    case -20: /* escp: \ */
        switch (ret = rch()) {
        case '/': ret = '/'; break; /* \/ avoid comment */
        case '<': ret = 29; break;
        case '>': ret = 30; break;
        case '%': ret = 31; break;
        }
        break;
    case -16: /* retread: !$%&()*+,-:=[]^ */
    case  -2: /* retread: 4(EOT), 10'\n', 59';' */
        ret = c;
        break;
    case -14: /* dquote: " */
        c = rsch(0);
        num = (rsch(0) << 8) | c;
        ret = 1;
        break;
    case -10: /* squote: ' */
        num = rsch(0);
        ret = 1;
        break;
    case -6: /* skip: / (comment) */
        do {
            ret = rch();
        } while (ret != 4/*EOT*/ && ret != '\n');
        break;
    case 0: /* string: < */
        putw(txtp, '<');
        for (numval = 0; (c = rsch(1)) >= 0; ++numval) {
            putw(txtp, c | 256);
        }
        putw(txtp, -1);
        return '<';
    default: /* ASCII */
        ch = c;
        if ('0' <= c && c <= '9') {
            ret = number(&num);
            break;
        }
        return rname();
    }
    putw(txtp, ret);
    if (ret == 1) {
        /* default(数字), squote, dquote */
        putw(txtp, numval = num);
    }
    return ret;
}

rsch(isstr)
{
    int c;
    c = rch();
    if (c == 4/*EOT*/ || c == '\n') {
        error("<");
        aexit();
    } else if (c == '\\') {
        switch (c = rch()) {
        case 'n': return 10;
        case 't': return  9;
        case 'e': return  4;
        case '0': return  0;
        case 'r': return 13;
        case 'a': return  6;
        case 'p': return 27;
        }
    } else if (isstr && c == '>') {
        return -1;
    }
    return c;
}
