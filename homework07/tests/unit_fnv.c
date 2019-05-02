/* unit_fnv.c */

#include "map.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Types */

typedef struct {
    char *	key;
    uint64_t	hash;
} Pair;

/* Constants */

static Pair TESTS[] = {
    {"wake me up inside", 9048950985493973590UL},
    {"123"              , 5003431119771845851UL},
    {"deadool"          , 9030128678874230203UL},
    {"wolverine"        , 9749463647854691528UL},
    {NULL               , 0},
};

/* Tests */

int test_00_fnv_hash() {
    /* Hash and check */
    for (size_t i = 0; TESTS[i].key; i++) {
    	uint64_t hash = fnv_hash(TESTS[i].key, strlen(TESTS[i].key));
    	printf("%20s = 0x%lx\n", TESTS[i].key, hash);
    	assert(TESTS[i].hash == hash);
    }
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test fnv_hash\n");
        return EXIT_FAILURE;
    }   

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_fnv_hash(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }
    
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
