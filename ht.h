typedef scruct ht ht;

// create has table and return pointer
ht* ht_create(void);

// frees memory allocated for hash table,
// including allocated keys
void ht_free(ht* table);

// Get item with given key (Nul-terminated) 
// from hash table, return value (set by ht_set)
// or NULL if key isn't found
void* ht_get(ht* table, const char* key);

// Set item with given key (NUL-terminated) to value
// If not already present in  table, key is copied
// to newly allocated memory. Return address of 
// copied key, or NULL 
const char* ht_set(ht* table, const char* key,
                    void* value);
// return number of items in ht
size_t ht_length(ht* table);

typedef struct {
    const char* key;
    void* value;

    ht*_table;
    sie_t _index;
} hti;

hti ht_iterator(ht*table);

bool ht_next(hti* it);



