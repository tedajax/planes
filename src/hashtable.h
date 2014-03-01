#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "types.h"
#include "dynarr.h"

typedef struct hashtable_node_t {
	char *key;
	void *value;
} HashTableNode;

typedef struct hashtable_t {
	u32 bucketCount;
	DynArr **buckets;
} HashTable;

HashTable *hashtable_new(u32 capacity);

//insert data into hashtable with given key
//if key does not exist in hash table, inserts value with key and returns true
//otherwise returns false and does not insert value
bool hashtable_insert(HashTable *self, const char *key, void *data);

//returns value stored with key or NULL if it is not found
void *hashtable_get(HashTable *self, const char *key);

//removes value stored at key and returns it
void *hashtable_remove(HashTable *self, const char *key);

u64 _hashtable_djb2(const unsigned char *key);
u32 _hashtable_index(HashTable *self, const char *key);

#endif