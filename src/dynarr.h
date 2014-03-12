#ifndef _DYN_ARR_H_
#define _DYN_ARR_H_

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "types.h"

typedef void(*free_func)(void *);

typedef struct dynarr_t {
	u32 size;
	u32 capacity;
	free_func freeFunc;
	void **data;
} DArr;

DArr *darr_new(u32 capacity);
void darr_setFreeFunc(DArr *self, free_func freeFunc);
void darr_add(DArr *self, void *element);
void *darr_index(DArr *self, u32 index);
bool darr_remove(DArr *self, void *element);
bool darr_removeAt(DArr *self, u32 index);

void _darr_resize(DArr *self, u32 capacity);

#endif