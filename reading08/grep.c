/*
 * Filename: grep.c
 * Author: John Quinn
 *
 * Notes: Set tabstop to 2
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * PROGRAM_NAME = NULL;
char * cmp = NULL;

void usage (int status) {
	fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
	exit(status);
}

void grep_stream (FILE * stream, char * cmp) {
	char buffer[BUFSIZ];
	while (fgets(buffer, BUFSIZ, stream)) {
		if (strstr(buffer, cmp)) {
			fputs(buffer, stdout);
		}
	}
}

void grep_file (const char * path, char * cmp) {
	FILE * fs = fopen(path, "r");
	if (fs == NULL) {
		fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
		return;
	}
	grep_stream(fs, cmp);
	fclose(fs);
}

int main (int argc, char * argv[]) {
	int argind = 1;
	PROGRAM_NAME = argv[0];
	while ( (argind < argc) && (strlen(argv[argind]) > 1) && (argv[argind][0] == '-') ) {
		char * arg = argv[argind++];
		switch (arg[1]) {
			case 'h':
				usage(0);
				break;
			default:
				usage(1);
				break;
		}
	}
	if (argc == 1) usage(1);
	cmp = argv[1];
	argind++;
	if (argind == argc) {
		grep_stream(stdin, cmp);
	} else {
		while (argind < argc) {
			char * path = argv[argind++];
			if (strcmp(path, "-") == 0) {
				grep_stream(stdin, cmp);
			} else {
				grep_file(path, cmp);
			}
		}
	}
	return EXIT_SUCCESS;
}
