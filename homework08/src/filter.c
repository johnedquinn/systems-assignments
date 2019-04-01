/* search_filter.c: Filters */

#include "search.h"

#include <errno.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>

/* Internal Filter Functions */

bool        filter_access(const char *path, const struct stat *stat, const Options *options) {
    return false;
}

FilterFunc FILTER_FUNCTIONS[] = {   /* Array of function pointers. */
    filter_access,
    NULL,
};

/* External Filter Functions */

/**
 * Filter path based options.
 * @param   path        Path to file to filter.
 * @param   options     Pointer to Options structure.
 * @return  Whether or not the path should be filtered out (false means include
 * it in output, true means exclude it from output).
 **/
bool	    filter(const char *path, const Options *options) {
    return false;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
