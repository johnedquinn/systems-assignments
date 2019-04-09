/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s files...\n", progname);
    exit(status);
}

/**
 * Save list of file paths to temporary file.
 * @param   files       Array of path strings.
 * @param   n           Number of path strings.
 * @return  Newly allocated path to temporary file.
 */
char *	save_files(char **files, size_t n) {
    /* Create temporary file */

    /* Write list of file paths to temporary file */

    return NULL;
}

/**
 * Run $EDITOR on specified path.
 * @param   path        Path to file to edit.
 * @return  Whether or not the $EDITOR process terminated successfully.
 */
bool	edit_files(const char *path) {
    /* Determine editor from environment */

    /* Fork child process and execute editor on specified path;
     * Parent waits for child and checks exit status of child process */
    return false;
}

/**
 * Rename files as specified in contents of path.
 * @param   files       Array of old path names.
 * @param   n           Number of old path names.
 * @param   path        Path to file with new names.
 * @return  Whether or not all rename operations were successful.
 */
bool	move_files(char **files, size_t n, const char *path) {
    /* Open specified path and read new name of files */

    /* For each file argument and new file name, attempt to rename if the names
     * don't match */
    return false;
}

/* Main Execution */

int	main(int argc, char *argv[]) {
    /* Parse command line options */

    /* Save files */

    /* Edit files */

    /* Move files */
    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
