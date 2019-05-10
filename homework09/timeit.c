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
char ** parse_options(int argc, char ** argv) {

    // Initialization
    char * PROGRAM_NAME = argv[0];
    int argind = 1;
    
    // Simple check
    if (argc == 1) usage(PROGRAM_NAME, 1);

    /* Parse command-line */
    while ( (argind < argc) && (strlen(argv[argind]) > 1) && (argv[argind][0] == '-') ) {
        char * arg = argv[argind++];
        if (streq(arg, "-h")) {
            usage(PROGRAM_NAME, 0);
        } else if (streq(arg, "-t")) {
            Timeout = atoi(argv[argind++]);
        } else if (streq(arg, "-v")) {
            Verbose = true;
        } else {
            usage(PROGRAM_NAME, 1);
        }
    }

    // Debug messages
    debug("Timeout = %d\n", Timeout);
    debug("Verbose = %d\n", Verbose);

    // Exit if no more arguments
    if (argind >= argc) usage(PROGRAM_NAME, 1);

    // Set the command
    int numStrings = argc - argind + 1; // 2
    char ** command = calloc(numStrings, sizeof(char *));
    for (size_t i = 0; i < (numStrings - 1); i++) {
        command[i] = argv[argind++];
    }

    // Debug for Command
    if (command && Verbose) {
        debug("Command = %s", command[0]);
        for (size_t i = 1; i < (numStrings - 1); i++)
            fprintf(stderr, " %s", command[i]);
        fprintf(stderr, "\n");
    }

    return command;
}




/**
 * Handle signal.
 * @param   signum      Signal number.
 */
void handle_signal(int signum) {
    debug("Received interrupt: %d\n", signum);
}





/* Main Execution */

int main(int argc, char * argv[]) {

    // Initialization
    struct timespec pre_time, post_time;
    int status = EXIT_SUCCESS;

    /* Parse command line options */
    char ** command = parse_options(argc, argv);

    /* Register handlers */
    signal(SIGCHLD, handle_signal);
    debug("Registering handlers...\n");

    // Get start time
    debug("Grabbing start time...\n");
    clock_gettime(CLOCK_MONOTONIC, &pre_time);

    // Fork
    pid_t pid = fork();

    
    if (pid < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        free(command);
        return EXIT_FAILURE;

    } else if (pid == 0) { // Child
        debug("Executing child...\n");
        if (execvp(command[0], command) < 0) {
            fprintf(stderr, "Unable to execute: %s\n", strerror(errno));
            free(command);
            exit(EXIT_FAILURE);
        }

    } else { // Parent
        debug("Sleeping for %d seconds...\n", Timeout);
        if (nanosleep((const struct timespec[]){{Timeout, 0}}, NULL) >= 0) {
            debug("Killing child %d...\n", pid);
            kill(pid, SIGKILL);
        }
        debug("Waiting for child %d...\n", pid);
        while ((pid = wait(&status)) < 0);
        status = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
        debug("Child exit status: %d\n", status);
    }

    // Grab end time
    debug("Grabbing end time...\n");
    clock_gettime(CLOCK_MONOTONIC, &post_time);

    // Compute total time
    float total_time = post_time.tv_sec - pre_time.tv_sec;
    printf("Time Elapsed: %.1f\n", total_time);

    // Free the command
    free(command);

    // WIFEXITED
    WIFEXITED(status);

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
