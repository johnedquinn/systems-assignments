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
int         walk(const char *root, const Options *options) {
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
