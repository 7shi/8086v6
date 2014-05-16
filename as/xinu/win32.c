#ifdef _WIN32
static char buf[256 * 1024];
static char *ps = &buf[0], *pe = &buf[sizeof(buf)];

void *sbrk(int size)
{
    char *ret = ps;
    if (ps + size > pe) return (void *)-1;
    ps += size;
    return ret;
}
#endif
