typedef struct {
    const char* key;
    void* value;
} ht_entry;

struct ht {
    ht_entry* entries;
    size_t capacity;
    size_t length;
};

ht* ht_create(void) {
    // Allocate space for hash table struct
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITITAL_CAPACITY;

    // Allocate (zero'd) space for entry buckets
    table->entries = calloc(table->capacity, size0f(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_free(ht* table) {
    // First free allocated keys
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) {
            free((void*)table->entries[i].key);
        }
    }

    // Free entries array and table itself
    free(table->entries);
    free(table);
}
}
