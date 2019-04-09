/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0
#define debug(M, ...) \
    if (Verbose) { \
        fprintf(stderr, "%s:%d:%s: " M, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    }

/* Globals */

int  Timeout = 10;
bool Verbose = false;

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] command...\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -t SECONDS  Timeout duration before killing command (default is %d)\n", Timeout);
    fprintf(stderr, "    -v          Display verbose debugging output\n");
    exit(status);
}

/**
 * Parse command line options.
 * @param   argc        Number of command line arguments.
 * @param   argv        Array of command line argument strings.
 * @return  Array of strings representing command to execute.
 */
char ** parse_options(int argc, char **argv) {
    return NULL;
}

/**
 * Handle signal.
 * @param   signum      Signal number.
 */
void    handle_signal(int signum) {
    debug("Received interrupt: %d\n", signum);
}

/* Main Execution */

int	main(int argc, char *argv[]) {
    /* Parse command line options */

    /* Register handlers */

    /* Fork child process... parent can either sleep and kill or set alarm */

    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
