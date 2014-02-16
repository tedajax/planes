#include "dynarr.h"

DynArr *dynArr_new(u32 capacity) {
	DynArr *self = (DynArr *)malloc(sizeof(DynArr));

	self->size = 0;
	self->freeFunc = NULL;
	self->data = NULL;
	_dynArr_resize(self, capacity);

	return self;
}

void dynArr_setFreeFunc(DynArr *self, free_func freeFunc) {
	assert(self);
	assert(freeFunc);
	self->freeFunc = freeFunc;
}

void dynArr_add(DynArr *self, void *element) {
	assert(self);
	assert(element);

	if (self->size >= self->capacity) {
		_dynArr_resize(self, self->capacity * 2);
	}

	self->data[self->size] = element;
	++self->size;
}

void *dynArr_index(DynArr *self, u32 index) {
	assert(self);

	if (index >= self->size) {
		return NULL;
	}

	return self->data[index];
}

bool dynArr_remove(DynArr *self, void *element) {
	assert(self);
	assert(element);

	for (int i = 0; i < self->size; ++i) {
		if (self->data[i] == element) {
			return dynArr_removeAt(self, i);;
		}
	}

	return false;
}

bool dynArr_removeAt(DynArr *self, u32 index) {
	assert(self);

	if (index >= self->size) {
		return false;
	}

	if (self->freeFunc != NULL) {
		self->freeFunc(self->data[index]);
	} else {
		free(self->data[index]);
	}

	u32 i = index;
	while (i + 1 < self->size) {
		self->data[i] = self->data[i + 1];
		++i;
	}

	--self->size;

	return true;
}

void _dynArr_resize(DynArr *self, u32 capacity) {
	assert(self);

	if (capacity <= self->size) {
		capacity = self->size + 1;
	}

	self->capacity = capacity;
	self->data = realloc(self->data, sizeof(void *) * capacity);
}