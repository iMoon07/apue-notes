#include "moon.h"

int
main(void)
{
    int c;

    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            jancuk_error("output error");
        }
    }

    if (ferror(stdin)) {
        jancuk_error("input error");
    }

    exit(0);
}
