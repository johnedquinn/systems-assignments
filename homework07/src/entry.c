/* entry.c: map entry */

#include "map.h"

/**
 * Create entry structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   next            Reference to next entry.
 * @param   type            Entry's value's type.
 * @return  Allocated Entry structure.
 */
Entry * entry_create(const char * key, const Value value, Entry * next, Type type) {
    Entry * e = malloc(sizeof(Entry));
    if (e) {
        e->key = strdup(key);
        e->type = type;
        if (type == STRING) e->value.string = strdup(value.string);
        else e->value = value;
        entry_update(e, value, type);
        e->next = next;
    }
    return e;
}

/**
 * Delete entry structure.
 * @param   e               Entry structure.
 * @param   recursive       Whether or not to delete remainder of entries.
 * return   NULL.
 */
Entry * entry_delete(Entry * e, bool recursive) {
    if (e == NULL) return NULL;
    if (recursive) entry_delete(e->next, recursive);
    if (e->type == STRING) free(e->value.string);
    free(e->key);
    free(e);
    return NULL;
}

/**
 * Update entry's value.
 * @param   e               Entry structure.
 * @param   value           New value for entry.
 * @param   type            New value's type.
 */
void entry_update(Entry * e, const Value value, Type type) {
    if (e->type == STRING)
        free(e->value.string);
    if (type == STRING)
        e->value.string = strdup(value.string);
    else
        e->value = value;
    e->type = type;
}

/**
 * Format entry by writing to stream.
 * @param   e               Entry structure.
 * @param   stream          File stream to write to.
 * @param   mode            Format mode to use.
 */
void entry_format(Entry *e, FILE *stream, const Format mode) {
    if (mode == KEY) fprintf(stream, "%s\n", e->key);
    if (mode == KEY_VALUE) {
        if (e->type == STRING) fprintf(stream, "%s\t%s\n", e->key, e->value.string);
        else fprintf(stream, "%s\t%ld\n", e->key, e->value.number);
    }
    if (mode == VALUE) {
        if (e->type == STRING) fprintf(stream, "%s\n", e->value.string);
        else fprintf(stream, "%ld\n", e->value.number);
    }
    if (mode == VALUE_KEY) {
        if (e->type == STRING) fprintf(stream, "%s\t%s\n", e->value.string, e->key);
        else fprintf(stream, "%ld\t%s\n", e->value.number, e->key);
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
