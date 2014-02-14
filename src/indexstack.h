#ifndef _INDEX_STACK_H_
#define _INDEX_STACK_H_

#include "types.h"

typedef struct index_stack_t {
	i32 capacity;
	i32 head;
	i32 *indices;
} IndexStack;

IndexStack *indexStack_new(u32 capacity);
i32 indexStack_peek(IndexStack *self);
i32 indexStack_pop(IndexStack *self);
void indexStack_push(indexStack *self, u32 index);
void indexStack_free(indexStack *self);

#endif