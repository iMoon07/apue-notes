#include "moon.h"

static int
visible_entry(const struct dirent *entry)
{
    return entry->d_name[0] != '.';
}

int
main(int argc, char *argv[])
{
    struct dirent **entries;
    const char *directory;
    int count;
    int i;

    if (argc > 2)
        jancuk_error("usage: %s [directory_name]", argv[0]);

    if (argc == 2)
        directory = argv[1];
    else
        directory = ".";

    count = scandir(directory, &entries, visible_entry, alphasort);

    if (count == -1)
        jancuk_error("can't open %s", directory);

    for (i = 0; i < count; i++) {
        printf("%s\n", entries[i]->d_name);
        free(entries[i]);
    }

    free(entries);
    exit(0);
}
