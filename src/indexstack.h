#ifndef _INDEX_STACK_H_
#define _INDEX_STACK_H_

#include "globals.h"
#include "types.h"

#include <stdlib.h>
#include <assert.h>

typedef struct index_stack_t {
	i32 capacity;
	i32 head;
	u32 *indices;
} IndexStack;

IndexStack *indexStack_new(i32 capacity);
i32 indexStack_peek(IndexStack *self);
i32 indexStack_pop(IndexStack *self);
void indexStack_push(IndexStack *self, u32 index);
void indexStack_free(IndexStack *self);

#endif