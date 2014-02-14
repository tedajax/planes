#include "indexstack.h"

IndexStack *indexStack_new(i32 capacity) {
	IndexStack *newIS = (IndexStack *)malloc(sizeof(IndexStack));

	assert(capacity > 0);

	newIS->capacity = capacity;
	newIS->head = -1;
	newIS->indices = (u32 *)malloc(sizeof(u32) * capacity);

	return newIS;
}

i32 indexStack_peek(IndexStack *self) {
	if (self->head < 0) {
		return -1;
	}
	return self->indices[self->head];
}

i32 indexStack_pop(IndexStack *self) {
	if (self->head < 0) {
		return -1;
	}
	return self->indices[self->head--];
}

void indexStack_push(indexStack *self, u32 index) {
	if (self->head >= self->capacity) {
		STUBBED("reached maximum capcity of array, resize it");
		return;
	}

	self->indices[++self->head] = index;
}

void indexStack_free(indexStack *self) {
	free(self->indices);
	free(self);
}