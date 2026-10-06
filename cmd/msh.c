#include "moon.h"

#include <readline/history.h>
#include <readline/readline.h>

int
main(void)
{
    char *line;
    pid_t pid;
    int status;

    moon_face();

    while ((line = readline("\001\033[2D\002  ")) != NULL) {
        if (line[0] == '\0') {
            free(line);
            moon_face();
            continue;
        }

        add_history(line);

        if (strcmp(line, "exit") == 0) {
            free(line);
            break;
        }

        pid = fork();

        if (pid < 0) {
            free(line);
            jancuk_error("fork error");
        }

        if (pid == 0) {
            execlp(line, line, (char *)NULL);

            fprintf(stderr, "couldn't execute: %s\n", line);
            free(line);
            exit(127);
        }

        if (waitpid(pid, &status, 0) < 0) {
            free(line);
            jancuk_error("waitpid error");
        }

        free(line);

        moon_face();
    }

    clear_history();

    printf("\n");

    return (0);
}
