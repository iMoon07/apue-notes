/*
 * Header guard:
 * prevents moon.h from being included more than once.
 */

#ifndef MOON_H
#define MOON_H
#define _POSIX_C_SOURCE 200809L /* POSIX feature-test macro */

/*
 * Request POSIX.1-2008 interfaces before including system headers.
 *
 * Standard C headers:
 * stdio.h  : printf(), dprintf(), fopen(), FILE
 * stdlib.h : exit(), malloc(), free(), EXIT_FAILURE
 * stdarg.h : va_list type, va_start(), va_arg(), va_end()
 * string.h : strcmp(), strlen(), memcpy(), memset()
 * errno.h  : errno, EACCESS, ENOENT
 *
 * POSIX/Unix headers:
 * dirent.h : scandir(), readdir(), alphasort(), DIR, struct dirent
 * fcntl.h  : open(), openat(), creat(), fcntl(),
 *            O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL,
 *            O_TRUNC, O_APPEND, O_NONBLOCK, O_SYNC,
 *            F_GETFL, F_SETFL, F_DUPFD, O_ACCMODE
 * unistd.h : read(), write(), close(), getpid(),
 *            STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO
 * sys/wait : wait(). waitpid(). WIFEXITED(), WIFESTATUS()
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

#include <fcntl.h>

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
 * Moon project error handling.
 */

void jancuk_error(const char *fmt, ...);
void jancuk_dump(const char *fmt, ...);
void jancuk_quit(const char *fmt, ...);

/*
 * Moon terminal face prompt.
 */

void moon_face(void);

#endif /* MOON_H */
