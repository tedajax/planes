#include "entity.h"

const u32 STARTING_COMPONENT_CAPACITY = 8;

Entity *entity_new(i32 id) {
	Entity *newEntity = (Entity *)malloc(sizeof(Entity));

	newEntity->id = id;
	newEntity->enabled = false;
	newEntity->destroy = false;
	//todo: GDestroyNotify function for freeing components
	newEntity->components = g_ptr_array_sized_new(STARTING_COMPONENT_CAPACITY);

	return newEntity;
}

void entity_start(Entity *self) {
	self->enabled = true;
	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_start(c);
	}
}

void entity_update(Entity *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_update(c, dt);
	}
}

void entity_lateUpdate(Entity *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_lateUpdate(c, dt);
	}
}

void entity_render(Entity *self) {
	if (!self->enabled) {
		return;
	}
	
	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_render(c);
	}
}

void *entity_addComponent(Entity *self, ComponentType type) {
	Component *c = component_new(type);
	c->entity = self;
	if (self->enabled) {
		component_start(c);
	}
	g_ptr_array_add(self->components, c);

	return c->component;
}

void *entity_getComponent(Entity *self, ComponentType type) {
	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);

		if (c->type == type) {
			return c->component;
		}
	}

	return NULL;
}

bool entity_removeComponent(Entity *self, Component *component) {
	//todo: make this safe to use while components are updating
	return g_ptr_array_remove(self->components, component);
}