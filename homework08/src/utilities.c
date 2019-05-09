/* search_utilities.c: Utilities */

#include "search.h"

#include <errno.h>
#include <dirent.h>

/* Utility Functions */

/**
 * Checks whether or not the directory is empty.
 * @param   path    Path to directory.
 * @return  Whether or not the path is an empty directory.
 */
bool is_directory_empty(const char *path) {

    DIR * d = opendir(path);
    if (!d) return false;

    for (struct dirent * e = readdir(d); e; e = readdir(d)) {
        if (!streq(e->d_name, ".") && !streq(e->d_name, "..")) {
            closedir(d);
            return false;
        }
    }
    closedir(d);
    return true;
}

/**
 * Retrieves modification time of file.
 * @param   path    Path to file.
 * @return  The modification time of the file.
 */
time_t get_mtime(const char *path) {
    struct stat s;
    if (lstat(path, &s) < 0) return 0;
    return s.st_mtime;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
