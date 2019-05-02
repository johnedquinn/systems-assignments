/* test_map.c */

#include "map.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Tests */

int test_00_map_create() {
    /* Create map with defaults */
    Map *m = map_create(0, 0);
    assert(m != NULL);
    assert(m->capacity    == DEFAULT_CAPACITY);
    assert(m->load_factor == DEFAULT_LOAD_FACTOR);
    assert(m->size        == 0);
    free(m->buckets);
    free(m);

    /* Create map with custom arguments */
    m = map_create(2, 0.5);
    assert(m != NULL);
    assert(m->capacity    == 2);
    assert(m->load_factor == 0.5);
    assert(m->size        == 0);
    free(m->buckets);
    free(m);

    return EXIT_SUCCESS;
}

int test_01_map_delete() {
    const size_t NBUCKETS = 4;

    /* Create map and populate buckets */
    Map *m = map_create(NBUCKETS, 0);

    for (size_t i = 0; i < NBUCKETS; i++) {
        char k[BUFSIZ];
        sprintf(k, "%lu", i);
        m->buckets[i].next = entry_create(k, (Value)k, NULL, STRING);
        for (size_t j = 0; j < NBUCKETS; j++) {
            sprintf(k, "%lu", j);
            m->buckets[i].next = entry_create(k, (Value)k, m->buckets[i].next, STRING);
        }
    }

    /* Delete map */
    map_delete(m);
    return EXIT_SUCCESS;
}

int test_02_map_insert() {
    const size_t NBUCKETS = 8;

    char k[BUFSIZ];
    Map *m = map_create(NBUCKETS, 1.25);
    for (size_t i = 0; i < NBUCKETS/2; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        map_insert(m, k, (Value)(int64_t)i, NUMBER);
        assert(m->size == (i + 1));

        bool inserted = false;
        for (size_t b = 0; b < NBUCKETS && !inserted; b++) {
            inserted = m->buckets[b].next && \
                       streq(m->buckets[b].next->key, k) && \
                       m->buckets[b].next->value.number == i;
        }
        assert(inserted);

        /* Update */
        map_insert(m, k, (Value)(int64_t)(i*2), NUMBER);
        assert(m->size == (i + 1));

        bool updated = false;
        for (size_t b = 0; b < NBUCKETS && !updated; b++) {
            updated = m->buckets[b].next && \
                      streq(m->buckets[b].next->key, k) && \
                      m->buckets[b].next->value.number == i*2;
        }
        assert(updated);
    }
    assert(m->capacity == NBUCKETS);

    map_delete(m);
    return EXIT_SUCCESS;
}

int test_03_map_search() {
    char k[BUFSIZ];
    Map *m = map_create(0, 0);

    for (size_t i = 0; i < DEFAULT_CAPACITY/2; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        map_insert(m, k, (Value)(int64_t)i, NUMBER);
        assert(m->size == (i + 1));
    }
    assert(m->capacity == DEFAULT_CAPACITY);

    for (size_t i = 0; i < DEFAULT_CAPACITY/2; i++) {
        /* Search Success */
        sprintf(k, "%lx", i);
        assert(map_search(m, k) != NULL);
        /* Search Failure */
        sprintf(k, "-%lx", i);
        assert(map_search(m, k) == NULL);
    }

    map_delete(m);
    return EXIT_SUCCESS;
}

int test_04_map_remove() {
    char k[BUFSIZ];
    Map *m = map_create(0, 5.0);

    for (size_t i = 0; i < DEFAULT_CAPACITY*3; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        map_insert(m, k, (Value)(int64_t)i, NUMBER);
        assert(m->size == (i + 1));
        assert(map_search(m, k) != NULL);
    }
    assert(m->capacity == DEFAULT_CAPACITY);

    for (size_t i = DEFAULT_CAPACITY; i < DEFAULT_CAPACITY*3; i++) {
        sprintf(k, "%lx", i);
        assert(map_remove(m, k) == true);
        assert(map_search(m, k) == NULL);
        assert(m->size == DEFAULT_CAPACITY*3 + DEFAULT_CAPACITY - i - 1);
        assert(map_remove(m, k) == false);
    }
    assert(m->size == DEFAULT_CAPACITY);
    map_delete(m);
    return EXIT_SUCCESS;
}

int test_05_map_format() {
    const size_t NBUCKETS = 8;

    char k[BUFSIZ];
    Map *m = map_create(NBUCKETS, 1.25);
    for (size_t i = 0; i < NBUCKETS/2; i++) {
        sprintf(k, "%ld", i);
        /* Insert */
        map_insert(m, k, (Value)(int64_t)(i*2), NUMBER);
    }

    char p[BUFSIZ] = "/tmp/test_map_XXXXXX";
    int  fd = mkstemp(p);
    assert(fd > 0);
    unlink(p);
    FILE *fs = fdopen(fd, "r+");
    assert(fs);

    /* Dump to temporary file */
    map_format(m, fs, KEY);
    assert(fseek(fs, 0, SEEK_SET) == 0);

    /* Read from temporary file */
    char b[BUFSIZ];
    int t = 0;
    while (fgets(b, BUFSIZ, fs)) {
        t += atoi(b);
    }
    assert(t == 6);

    /* Dump to temporary file */
    assert(fseek(fs, 0, SEEK_SET) == 0);
    map_format(m, fs, VALUE);

    /* Read from temporary file */
    assert(fseek(fs, 0, SEEK_SET) == 0);
    t = 0;
    while (fgets(b, BUFSIZ, fs)) {
        t += atoi(b);
    }
    assert(t == 12);

    fclose(fs);
    map_delete(m);
    return EXIT_SUCCESS;
}

int test_06_map_resize() {
    char k[BUFSIZ];
    Map *m = map_create(0, 0);

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        map_insert(m, k, (Value)(int64_t)i, NUMBER);
        assert(m->size == (i + 1));
    }
    assert(m->capacity > DEFAULT_CAPACITY);

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++) {
        /* Search Success */
        sprintf(k, "%lx", i);
        assert(map_search(m, k) != NULL);
        /* Search Failure */
        sprintf(k, "-%lx", i);
        assert(map_search(m, k) == NULL);
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++) {
        sprintf(k, "%lx", i);
        assert(map_remove(m, k) == true);
        assert(map_search(m, k) == NULL);
        assert(m->size == DEFAULT_CAPACITY - i - 1);
        assert(map_remove(m, k) == false);
    }
    assert(m->size == 0);
    assert(m->capacity > DEFAULT_CAPACITY);

    map_delete(m);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test map_create\n");
        fprintf(stderr, "    1  Test map_delete\n");
        fprintf(stderr, "    2  Test map_insert\n");
        fprintf(stderr, "    3  Test map_search\n");
        fprintf(stderr, "    4  Test map_remove\n");
        fprintf(stderr, "    5  Test map_format\n");
        fprintf(stderr, "    6  Test map_resize\n");
        return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_map_create(); break;
        case 1:  status = test_01_map_delete(); break;
        case 2:  status = test_02_map_insert(); break;
        case 3:  status = test_03_map_search(); break;
        case 4:  status = test_04_map_remove(); break;
        case 5:  status = test_05_map_format(); break;
        case 6:  status = test_06_map_resize(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
