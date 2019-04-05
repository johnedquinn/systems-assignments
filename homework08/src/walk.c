/* search_walk.c: Walk */

#include "search.h"

#include <errno.h>
#include <dirent.h>

/* Walk Functions */

/**
 * Recursively walk the root directory with specified options.
 * @param   root        Root directory path.
 * @param   options     User specified filter options.
 * @return  Whether or not walking this directory was successful.
 */
int walk(const char * root, const Options * options) {

    // Set directory
    DIR * d = opendir(root);
    if (!d) return EXIT_FAILURE;

    // Walk through directory
    for (struct dirent * e = readdir(d); e; e = readdir(d)) {
        struct stat s;
        char path[BUFSIZ];

        // Don't examine current directory or parent
        if (streq(e->d_name, ".") || streq(e->d_name, "..")) continue;

        // Form full path with root and entry
        snprintf(path, BUFSIZ, "%s/%s", root, e->d_name);

        if(lstat(path, &s) < 0) continue;

        // Recurse into directories and output files
        if (!filter(path, options))
            puts(path);
        if (S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
            walk(path, options);

    }

    closedir(d);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
