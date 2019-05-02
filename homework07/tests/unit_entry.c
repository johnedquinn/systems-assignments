/* unit_entry.c */

#include "map.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Constants */

static char *KEY0 = "123";
static char *KEY1 = "wake me up inside";

/* Tests */

int test_00_entry_create() {
    /* Create one entry */
    Entry *e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);

    assert(e0);
    assert(streq(e0->key, KEY0));
    assert(e0->value.number == strtol(KEY0, NULL, 10));
    assert(e0->next == NULL);
    assert(e0->type == NUMBER);

    /* Create one entry linked to previous entry */
    Entry *e1 = entry_create(KEY1, (Value)KEY1, e0, STRING);
    assert(e1);
    assert(streq(e1->key, KEY1));
    assert(streq(e1->value.string, KEY1));
    assert(e1->next == e0);
    assert(e1->type == STRING);

    free(e0->key);
    free(e0);
    free(e1->key);
    free(e1->value.string);
    free(e1);

    return EXIT_SUCCESS;
}

int test_01_entry_delete() {
    /* Create and delete one entry */
    Entry *e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(e0);

    e0 = entry_delete(e0, false);
    assert(e0 == NULL);
    
    /* Create and delete two linked entries */
    e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(e0);
    
    Entry *e1 = entry_create(KEY1, (Value)KEY1, e0, STRING);
    assert(e1);
    
    e1 = entry_delete(e1, true);
    assert(e1 == NULL);

    /* Create and delete ten linked entries */
    Entry *head = NULL;
    for (int i = 0; i < 10; i++) {
        head = entry_create(KEY0, (Value)KEY0, head, STRING);
        assert(head);
    }
    head = entry_delete(head, true);
    assert(head == NULL);

    /* NULL check */
    entry_delete(NULL, false);
    return EXIT_SUCCESS;
}

int test_02_entry_update() {
    /* Create and update entry */
    Entry *e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(e0);
    assert(streq(e0->key, KEY0));
    assert(e0->value.number == strtol(KEY0, NULL, 10));
    assert(e0->next == NULL);
    assert(e0->type == NUMBER);

    entry_update(e0, (Value)KEY1, STRING);
    assert(strcmp(e0->value.string, KEY1) == 0);

    /* Create and update entry */
    Entry *e1 = entry_create(KEY1, (Value)KEY1, e0, STRING);
    assert(e1);
    assert(streq(e1->key, KEY1));
    assert(streq(e1->value.string, KEY1));
    assert(e1->next == e0);
    assert(e1->type == STRING);
    entry_update(e1, (Value)strtol(KEY0, NULL, 10), NUMBER);
    assert(e1->value.number == strtol(KEY0, NULL, 10));

    e0 = entry_delete(e0, false);
    assert(e0 == NULL);

    e1 = entry_delete(e1, false);
    assert(e1 == NULL);
    return EXIT_SUCCESS;
}

int test_03_entry_format() {
    /* Create temporary file */
    char path[BUFSIZ] = "/tmp/test_entry_XXXXXXX";
    int   fd = mkstemp(path);
    assert(fd > 0);
    unlink(path);

    FILE *fs = fdopen(fd, "w+");
    assert(fs);

    /* Dump entry to file */
    Entry *e0 = entry_create(KEY0, (Value)KEY1, NULL, STRING);
    entry_format(e0, fs, KEY);
    entry_format(e0, fs, KEY_VALUE);
    entry_format(e0, fs, VALUE);
    entry_format(e0, fs, VALUE_KEY);

    /* Rewind file */
    assert(fseek(fs, 0, SEEK_SET) == 0);

    /* Read entry output */
    char buffer[BUFSIZ];
    assert(fgets(buffer, BUFSIZ, fs));
    assert(streq(buffer, "123\n"));

    assert(fgets(buffer, BUFSIZ, fs));
    assert(streq(buffer, "123\twake me up inside\n"));

    assert(fgets(buffer, BUFSIZ, fs));
    assert(streq(buffer, "wake me up inside\n"));

    assert(fgets(buffer, BUFSIZ, fs));
    assert(streq(buffer, "wake me up inside\t123\n"));

    entry_delete(e0, true);
    fclose(fs);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test entry_create\n");
        fprintf(stderr, "    1  Test entry_delete\n");
        fprintf(stderr, "    2  Test entry_update\n");
        fprintf(stderr, "    3  Test entry_format\n");
        return EXIT_FAILURE;
    }   

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_entry_create(); break;
        case 1:  status = test_01_entry_delete(); break;
        case 2:  status = test_02_entry_update(); break;
        case 3:  status = test_03_entry_format(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }
    
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
