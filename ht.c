#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct {
    const char* key;
    void* value;
} ht_entry;

struct ht {
    ht_entry* entries;
    size_t capacity;
    size_t length;
};

static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

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

void* ht_get(ht* table, const char* key) {
    // AND hash with capacity minus 1 to ensurs 
    // it's within entires array
    uint64_t hash = hash_key(key);
    size_t index = 
    (size_t)(hash & (uint64_t)(table->capacity -1));
    
    // Loop till we find an empty entry
    while (table->entires[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) =0) {
        return table->entries[index].value;
        }
        // key wasn't here, move to next
        // linear probing
        index ++;
        if (index >= table->capacity) {
            // at end of entries array, wrap around
            index = 0;
        }
    }
    
    return NULL;
}
