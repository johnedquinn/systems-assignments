/* search_options.c: Options */

#include "search.h"

#include <unistd.h>

/* Options Functions */

/**
 * Display usage message and exit.
 * @param   progname        Name of program.
 * @param   status          Exit status.
 */
void        options_usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS]\n", progname);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -help           Display this help message\n\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  PATTERN  Base of file name matches shell PATTERN\n");
    fprintf(stderr, "    -path  PATTERN  Path of file matches shell PATTERN\n\n");
    fprintf(stderr, "    -perm  MODE     File's permission bits are exactly MODE (octal)\n");
    fprintf(stderr, "    -newer fILE     File was modified more recently than FILE\n\n");
    fprintf(stderr, "    -uid   N        File's numeric user ID is N\n");
    fprintf(stderr, "    -gid   N        File's numeric group ID is N\n");
    exit(status);
}

/**
 * Parse command-line options.
 * @param   argc            Number of command-line arguments.
 * @param   argv            Array of command-line arguments.
 * @param   root            Pointer to root string.
 * @param   options         Pointer to Options structure.
 * @return  Whether or not parsing the command-line options was successful.
 */
bool        options_parse(int argc, char **argv, char **root, Options *options) {
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
