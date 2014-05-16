#ifdef _WIN32
#include <windows.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

int mkstemp(char fn[PATH_MAX])
{
    int ret, len;
    if (!strncmp(fn, "/tmp/", 5)) {
        char buf[PATH_MAX];
        GetTempPath(sizeof(buf), buf);
        strncat(buf, &fn[5], PATH_MAX - 1);
        strncpy(fn, buf, PATH_MAX - 1);
    }
    len = strlen(fn);
    if (len < 6 || strcmp(&fn[len - 6], "XXXXXX")) return -1;
    srand(time(NULL));
    do {
        int i;
        for (i = len - 6; i < len; ++i) {
            fn[i] = '0' + ((rand() >> 3) % 10);
        }
        ret = open(fn, O_CREAT | O_EXCL | O_BINARY | O_WRONLY, S_IWRITE);
    } while (ret == -1 && errno == EEXIST);
    return ret;
}

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
