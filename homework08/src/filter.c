/* search_filter.c: Filters */

#include "search.h"

#include <errno.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>

/* Internal Filter Functions */

bool filter_access(const char * path, const struct stat * stat, const Options * options) {
    return options->access && access(path, options->access) != 0;
}

bool filter_type(const char * path, const struct stat * stat, const Options * options) {
    if (options->type == S_IFREG)
        return options->type && (options->type == (stat->st_mode && S_IFMT) || S_ISDIR(stat->st_mode) || S_ISLNK(stat->st_mode));
    if (options->type == S_IFDIR)
        return options->type == stat->st_mode || !S_ISDIR(stat->st_mode);
    return false;
}

bool filter_empty(const char * path, const struct stat * stat, const Options * options) {
    return options->empty && ( (S_ISDIR(stat->st_mode) && !is_directory_empty(path) ) || (!S_ISDIR(stat->st_mode) && stat->st_size != 0) );
}

bool filter_name(const char *path, const struct stat *stat, const Options *options) {
    char * name = strrchr(path, '/') + 1;
    return options->name && fnmatch(options->name, name, 0) != 0;
}

bool filter_path(const char * path, const struct stat * stat, const Options * options) {
    return options->path && fnmatch(options->path, path, 0) != 0;
}

bool filter_perm(const char * path, const struct stat * stat, const Options * options) {
    return options->perm && (stat->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) != options->perm;
}

bool filter_newer(const char *path, const struct stat *stat, const Options *options) {
    return options->newer && get_mtime(path) <= options->newer;
}

bool filter_uid(const char *path, const struct stat *stat, const Options *options) {
    return options->uid >= 0 && options->uid != stat->st_uid;
}

bool filter_gid(const char *path, const struct stat *stat, const Options *options) {
    return options->gid >= 0 && options->gid != stat->st_gid;
}

FilterFunc FILTER_FUNCTIONS[] = {   /* Array of function pointers. */
    filter_access,
    filter_type,
    filter_empty,
    filter_name,
    filter_path,
    filter_perm,
    filter_newer,
    filter_uid,
    filter_gid,
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
bool filter(const char * path, const Options * options) {
    
    // Read meta-data from file
    struct stat s;
    if (lstat(path, &s) < 0) return EXIT_FAILURE;

    /*if ( filter_access(path, &s, options)
        || filter_type(path, &s, options)
        || filter_empty(path, &s, options)
        || filter_name(path, &s, options)
        || filter_path(path, &s, options)
        || filter_perm(path, &s, options)
        || filter_newer(path, &s, options)
        || filter_uid(path, &s, options)
        || filter_gid(path, &s, options) ) { return true; }*/

    for (size_t i = 0; FILTER_FUNCTIONS[i] != NULL; i++) {
        if ((*FILTER_FUNCTIONS[i])(path, &s, options)) return true;
    }

    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
