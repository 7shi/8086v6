/* translated from as23.s */

struct Op { char type, num; int value; };
struct Op *curfb[], *nxtfb[], *fbbufp;

fbadv(num)
{
    struct Op *fb;
    fb = curfb[num] = nxtfb[num];
    if (!fb) fb = fbbufp - 1;
    do {
        ++fb;
    } while (fb->type >= 0 && fb->num != num);
    nxtfb[num] = fb;
}
