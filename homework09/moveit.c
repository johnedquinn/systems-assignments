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
void usage(const char * progname, int status) {
    fprintf(stderr, "Usage: %s files...\n", progname);
    exit(status);
}




/**
 * Save list of file paths to temporary file.
 * @param   files       Array of path strings.
 * @param   n           Number of path strings.
 * @return  Newly allocated path to temporary file.
 */
char * save_files(char ** files, size_t n) {
    /* Create temporary file */
    char temp [] = "john.XXXXXX";

    int fd = 0;
    if ((fd = mkstemp(temp)) == -1) {
        fprintf(stderr, "Couldn't get file descriptor: %s\n", strerror(errno));
        _exit(EXIT_FAILURE);
    }

    FILE * tempFile = NULL;
    if ((tempFile = fdopen(fd, "w+")) == NULL) {
        fprintf(stderr, "Couldn't open temp file: %s\n", strerror(errno));
        _exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++) {
        fprintf(tempFile, "%s\n", files[i]);
    }

    fclose(tempFile);

    /* Write list of file paths to temporary file */

    return strdup(temp);
}




/**
 * Run $EDITOR on specified path.
 * @param   path        Path to file to edit.
 * @return  Whether or not the $EDITOR process terminated successfully.
 */
bool edit_files(const char * path) {

    /* Determine editor from environment */
    char * editor = getenv("EDITOR") ? getenv("EDITOR") : "vim";

    /* Fork child process and execute editor on specified path;
     * Parent waits for child and checks exit status of child process */

    int status = EXIT_SUCCESS;
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return false;
    } else if (pid == 0) {
        if (execlp(editor, editor, path, NULL) < 0) {
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
            return false;
        }
    } else {
        while ((pid = wait(&status)) < 0);
    }

    return (status == EXIT_SUCCESS) ? true: false;
}






/**
 * Rename files as specified in contents of path.
 * @param   files       Array of old path names.
 * @param   n           Number of old path names.
 * @param   path        Path to file with new names.
 * @return  Whether or not all rename operations were successful.
 */
bool move_files(char ** files, size_t n, const char * path) {

    /* Open specified path and read new name of files */
    FILE * tfs = NULL;
    if ((tfs = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Can't open the path: %s\n", strerror(errno));
        return false;
    }

    /* For each file argument and new file name, attempt to rename if the names
     * don't match */
    char new_path[BUFSIZ];
    size_t i = 0;
    while (fgets(new_path, BUFSIZ, tfs) && i < n) {
        strchomp(new_path);
        if (!streq(files[i], new_path)) {
            if (rename(files[i], new_path) < 0) {
                fclose(tfs);
                return false;
            }
        }
        i++;
    }
    fclose(tfs);
    return true;
}







/* Main Execution */

int main(int argc, char * argv[]) {

    const char * PROGRAM_NAME = argv[0];

    /* Check arguments */
    if (argc == 1) usage(PROGRAM_NAME, EXIT_FAILURE);
    if (streq(argv[1], "-h")) usage(PROGRAM_NAME, EXIT_SUCCESS);

    /* Save files */
    char * tpath = save_files(&argv[1], argc - 1);

    /* Edit files */
    if (edit_files(tpath) == false) {
        unlink(tpath);
        free(tpath);
        return EXIT_FAILURE;
    }

    /* Move files */
    if (move_files(&argv[1], argc - 1, tpath) == false) {
        unlink(tpath);
        free(tpath);
        return EXIT_FAILURE;
    }

    /* Close path */
    unlink(tpath);
    free(tpath);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
