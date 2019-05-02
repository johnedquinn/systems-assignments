/* map.c: separate chaining hash table */

#include "map.h"

/**
 * Create map data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @param   load_factor     Maximum load factor before resizing.
 * @return  Allocated Map structure.
 */
Map * map_create(size_t capacity, double load_factor) {
    Map * m = malloc(sizeof(Map));
    if (m) {
        m->capacity = (capacity == 0) ? DEFAULT_CAPACITY : capacity;
        m->load_factor = (load_factor <= 0) ? DEFAULT_LOAD_FACTOR : load_factor;
        m->size = 0;
        m->buckets = calloc(m->capacity, sizeof(Entry));
        if (! m->buckets) return NULL;
    }
    return m;
}

/**
 * Delete map data structure.
 * @param   m               Map data structure.
 * @return  NULL.
 */
Map * map_delete(Map * m) {
    for (size_t i = 0; i < m->capacity; i++)
        entry_delete(m->buckets[i].next, true);
    free(m->buckets);
    free(m);
    return NULL;
}

/**
 * Insert or update entry into map data structure.
 * @param   m               Map data structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   type            Entry's value's type.
 */
void map_insert(Map * m, const char * key, const Value value, Type type) {
    if ((double)m->size / m->capacity >= m->load_factor) map_resize(m, (m->capacity * 2));
    Entry * match = map_search(m, key);
    if (match) {
        entry_update(match, value, type);
    } else {
        int index = fnv_hash(key, strlen(key)) % m->capacity;
        m->buckets[index].next = entry_create(key, value, m->buckets[index].next, type);
        m->size = m->size + 1;
    }
}

/**
 * Search map data structure by key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to search for.
 * @param   Pointer to the entry with the specified key (or NULL if not found).
 */
Entry * map_search(Map * m, const char *key) {
    int index = fnv_hash(key, strlen(key)) % m->capacity;
    for (Entry * curr = m->buckets[index].next; curr; curr = curr->next) {
        if (strcmp(curr->key, key) == 0) return curr;
    }
    return NULL;
}

/**
 * Remove entry from map data structure with specified key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to remove.
 * return   Whether or not the removal was successful.
 */
bool map_remove(Map *m, const char *key) {
    int index = fnv_hash(key, strlen(key)) % m->capacity;
    Entry * prev = &(m->buckets[index]);
    Entry * curr = m->buckets[index].next;
    for (curr = curr; curr; curr = curr->next) {
        if (strcmp(curr->key, key) == 0) {
            prev->next = curr->next;
            entry_delete(curr, false);
            m->size = m->size - 1;
            return true;
        }
        prev = prev->next;
    }
    return false;
}

/**
 * Format all the entries in the map data structure.
 * @param   m               Map data structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void map_format(Map *m, FILE *stream, const Format mode) {
   for (size_t index = 0; index < m->capacity; index++)  {
        for (Entry * curr = m->buckets[index].next; curr; curr = curr->next) {
            entry_format(curr, stream, mode);
        }
    }
}

/**
 * Resize the map data structure.
 * @param   m               Map data structure.
 * @param   new_capacity    New capacity for the map data structure.
 */
void map_resize(Map *m, size_t new_capacity) {
    Entry * newBuckets = calloc(new_capacity, sizeof(Entry));
    for (size_t index = 0; index < m->capacity; index++) {
        //for (Entry * curr = m->buckets[index].next; curr; curr) {
        Entry * curr = m->buckets[index].next;
        while (curr) {
            Entry * next = curr->next;
            int newIndex = fnv_hash(curr->key, strlen(curr->key)) % new_capacity;
            curr->next = newBuckets[newIndex].next;
            newBuckets[newIndex].next = curr;
            curr = next;
        }
    }
    Entry * oldBuckets = m->buckets;
    m->capacity = new_capacity;
    m->buckets = newBuckets;
    free(oldBuckets);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
