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

const char* ht_set(ht* table, 
                   const char* key, 
                   void* value) {

        assert(value != NULL);
        if (value == NULL) {
            return NULL;
        }

        // if length will exceed half of current
        // capacity, expand it
        if (table->length >= table->capacity / 2) {
            if (!ht_expand(table)) {
                return NULL;
            }
        }

        // set entry and update length
        return ht_set_entry(table->entires, 
                            table->capacity,
                            key, value,
                            &table->length);
}
// set an entry without expanding table 
static const char* ht_set_entry(ht_entry* entries, 
                                size_t capacity,
                                const char* key,
                                void* value,
                                size_t* plength) {
    // AND hash with capacity minus 1 to ensure
    // it's within entries array
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity -1));

    // Loop till we find an empty array
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Found key, update value
            entries[index].value = value;
            return entries[index].key;
        }

        // key wasn't in the slot
        index++;
        if (index >= capacity) {
            index = 0;
        }
    }

    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }

    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}
    


