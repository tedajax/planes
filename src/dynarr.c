#include "dynarr.h"

DArr *darr_new(u32 capacity) {
	DArr *self = (DArr *)malloc(sizeof(DArr));

	self->size = 0;
	self->freeFunc = NULL;
	self->data = NULL;
	_darr_resize(self, capacity);

	return self;
}

void darr_setFreeFunc(DArr *self, free_func freeFunc) {
	assert(self);
	assert(freeFunc);
	self->freeFunc = freeFunc;
}

void darr_add(DArr *self, void *element) {
	assert(self);
	assert(element);

	if (self->size >= self->capacity) {
		_darr_resize(self, self->capacity * 2);
	}

	self->data[self->size] = element;
	++self->size;
}

void *darr_index(DArr *self, u32 index) {
	assert(self);

	if (index >= self->size) {
		return NULL;
	}

	return self->data[index];
}

bool darr_remove(DArr *self, void *element) {
	assert(self);
	assert(element);

	for (int i = 0; i < self->size; ++i) {
		if (self->data[i] == element) {
			return darr_removeAt(self, i);;
		}
	}

	return false;
}

bool darr_removeAt(DArr *self, u32 index) {
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

void _darr_resize(DArr *self, u32 capacity) {
	assert(self);

	if (capacity <= self->size) {
		capacity = self->size + 1;
	}

	self->capacity = capacity;
	self->data = realloc(self->data, sizeof(void *) * capacity);
}