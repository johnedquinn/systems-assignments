/* main.c: string library utility */


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

/* Globals */

char *PROGRAM_NAME = NULL;
int mode = 0;

/* Modes */


enum {
    STRIP = 1 << 0,
    REVERSE = 1 << 1,
    LOWER = 1 << 2,
    UPPER = 1 << 3
};


/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int mode) {

    char buffer[BUFSIZ];
    char * buffPoint = buffer;
    while (fgets(buffer, BUFSIZ, stream)) {
        str_chomp(buffPoint);
        str_translate(buffPoint, source, target);
        buffPoint = buffer;
        if (mode & STRIP)
            buffPoint = str_strip(buffPoint);

        if (mode & REVERSE)
            buffPoint = str_reverse(buffPoint);

        if (mode & LOWER)
            buffPoint = str_lower(buffPoint);

        if (mode & UPPER)
            buffPoint = str_upper(buffPoint);

        printf(buffPoint);
        printf("\n");
    }

}

/* Main Execution */

int main(int argc, char *argv[]) {

    /* PARSE COMMAND-LINE ARGUMENTS */
    int argind = 1;
    PROGRAM_NAME = argv[0];
    while ( (argind < argc) && (strlen(argv[argind]) > 1) && (argv[argind][0] == '-') ) {
        char * arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            case 's':
                mode |= STRIP;
                break;
            case 'r':
                mode |= REVERSE;
                break;
            case 'l':
                mode |= LOWER;
                break;
            case 'u':
                mode |= UPPER;
                break;
            default:
                usage(1);
                break;
        }
    }

    char * source = "";
    char * target = "";
    if (argv[argind]) {
        source = argv[argind++];
        target = argv[argind];
    }

    /* TRANSLATE STREAM */
    translate_stream(stdin, source, target, mode);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
