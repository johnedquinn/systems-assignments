/* search_main.c: Main Execution */

#include "search.h"

/* Main Execution */

int main(int argc, char *argv[]) {

    Options options = {0, .uid = -1, .gid = -1};

    /* Parse options */
    char * root = NULL;
    options_parse(argc, argv, &root, &options);

    /* Check root */
    if (!filter(root, &options)) puts(root);

    /* Walk root */
    walk(root, &options);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
