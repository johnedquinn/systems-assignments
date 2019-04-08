/* doit.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <unistd.h>

/**
 * Run specified program with the bourne shell.
 * @param     command     Command to run.
 * @return    Exit status of child process.
 */
int doit(const char *command) {
    int status = 0;
    
    pid_t pid = fork();
    if (pid < 0) {
        return EXIT_FAILURE;
    }

    if (pid == 0) { //Child
        if (execl("/bin/sh", "sh", "-c", command, NULL) < 0) {
            return EXIT_FAILURE;
        }
    } else { // Parent
        while ((pid = wait(& status)) < 0);
		}
    return status;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s COMMAND\n", argv[0]);
		return EXIT_SUCCESS;
	}
	return WEXITSTATUS(doit(argv[1]));
}

