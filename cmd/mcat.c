#include "moon.h"

#define BUFFSIZE 4096

static void
print_char(char c, int show_line_you, int *start_line,
    unsigned long *line)
{
    if (show_line_you && *start_line)
        dprintf(STDOUT_FILENO, "%6lu\t", *line);

    if (write(STDOUT_FILENO, &c, 1) != 1)
        jancuk_error("write error");

    if (c == '\n')
        (*line)++;

    *start_line = (c == '\n');
}

int
main(int argc, char *argv[])
{
    int n;
    int i;
    int show_line_you;
    int start_line;
    char buf[BUFFSIZE];
    unsigned long line;

    show_line_you = 0;
    if (argc == 2 && strcmp(argv[1], "-n") == 0)
        show_line_you = 1;

    line = 1;
    start_line = 1;

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        for (i = 0; i < n; i++)
            print_char(buf[i], show_line_you, &start_line, &line);

    if (n < 0)
        jancuk_error("read error");

    exit(0);
}
