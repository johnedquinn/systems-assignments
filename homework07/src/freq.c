/* freq.c */

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "    -f FORMAT        Output format (KEY, KEY_VALUE, VALUE, VALUE_KEY)\n");
    fprintf(stderr, "    -l LOAD_FACTOR   Load factor for hash table\n");
    exit(status);
}

void freq_stream(FILE *stream, double load_factor, Format mode) {
    char buffer[BUFSIZ];
    char * buffPoint = buffer;
    Map * m = map_create(0, load_factor);
    //while(fgets(buffer, BUFSIZ, stream)) {
    while(fgets(buffer, BUFSIZ, stream)) {
        if ( *(buffPoint + strlen(buffPoint) - 1) == '\n' ) *(buffPoint + strlen(buffPoint) - 1) = 0;
        char * token = strtok(buffer, " ");
        buffPoint = buffer;
        while (token != NULL) {
            Entry * found = map_search(m, token);
            if (!found)
                map_insert(m, token, (Value)(int64_t)1, NUMBER);
            else
                map_insert(m, token, (Value)(int64_t)(found->value.number + 1), NUMBER);
            token = strtok(NULL, " ");
        }
    }
    map_format(m, stdout, mode);
    map_delete(m); 
}

/* Main Execution */

int main(int argc, char *argv[]) {

    /* PARSE COMMAND-LINE ARGUMENTS */
    int argind = 1;
    PROGRAM_NAME = argv[0];
    Format FORMAT = VALUE_KEY;
    double LOAD_FACTOR = DEFAULT_LOAD_FACTOR;
    while ( (argind < argc) && (strlen(argv[argind]) > 1) && (argv[argind][0] == '-') ) {
        char * arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            case 'f':
                if (strcmp(argv[argind], "KEY") == 0) FORMAT = KEY;
                else if (strcmp(argv[argind], "KEY_VALUE") == 0) FORMAT = KEY_VALUE;
                else if (strcmp(argv[argind], "VALUE") == 0) FORMAT = VALUE;
                else if (strcmp(argv[argind], "VALUE_KEY") == 0) FORMAT = VALUE_KEY;
                else FORMAT = VALUE_KEY;
                argind++;
                break;
            case 'l':
                LOAD_FACTOR = strtod(argv[argind++], NULL);
                break;
            default:
                usage(1);
                break;
        }
    }

    

    freq_stream(stdin, LOAD_FACTOR, FORMAT);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

