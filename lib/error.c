#include "moon.h"

void
jancuk_error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}
