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
} DynArr;

DynArr *dynArr_new(u32 capacity);
void dynArr_setFreeFunc(DynArr *self, free_func freeFunc);
void dynArr_add(DynArr *self, void *element);
void *dynArr_index(DynArr *self, u32 index);
bool dynArr_remove(DynArr *self, void *element);
bool dynArr_removeAt(DynArr *self, u32 index);

void _dynArr_resize(DynArr *self, u32 capacity);

#endif