#include "moon.h"

int
main(void)
{
    fprintf(stderr, "meacces: %s\n", strerror(EACCES));
    
    errno = ENOENT;
    perror("merror");
    exit(0);
}
