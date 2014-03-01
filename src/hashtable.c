#include "hashtable.h"

HashTable *hashtable_new(u32 capacity) {
	HashTable *self = (HashTable *)malloc(sizeof(HashTable));

	self->bucketCount = capacity;
	self->buckets = (DynArr **)malloc(sizeof(DynArr *) * capacity);

	return self;
}

bool hashtable_insert(HashTable *self, const char *key, void *data) {
	return true;
}

void *hashtable_get(HashTable *self, const char *key) {
	return NULL;
}

void *hashtable_remove(HashTable *self, const char *key) {
	return NULL;
}

u64 _hashtable_djb2(const unsigned char *key) {
	u64 hash = 5381;
	i32 c;
	while ((c = *key++)) {
		hash = ((hash << 5) + hash) + c; //hash * 33 + c
	}
	return hash;
}

u32 _hashtable_index(HashTable *self, const char *key) {
	return _hashtable_djb2(key) % self->bucketCount;
}