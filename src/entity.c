#include "entity.h"

const u32 STARTING_COMPONENT_CAPACITY = 8;

Entity *entity_new(i32 id) {
	Entity *newEntity = (Entity *)malloc(sizeof(Entity));

	newEntity->id = id;
	newEntity->enabled = true;
	//todo: GDestroyNotify function for freeing components
	newEntity->components = g_ptr_array_sized_new(STARTING_COMPONENT_CAPACITY);

	return newEntity;
}

void entity_start(Entity *self) {
	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_start(c);
	}
}

void entity_update(Entity *self, f32 dt) {
	for (int i = 0; i < self->components->len; ++i) {
		if (self->components == NULL) {
			printf("what\n");
		}
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_update(c, dt);
	}

	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_lateUpdate(c, dt);
	}
}

void entity_render(Entity *self) {
	for (int i = 0; i < self->components->len; ++i) {
		Component *c = (Component *)g_ptr_array_index(self->components, i);
		component_render(c);
	}
}

void *entity_addComponent(Entity *self, ComponentType type) {
	Component *c = component_new(type);
	c->entity = self;
	component_start(c);
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