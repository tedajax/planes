#include "entity.h"

const u32 DEFAULT_COMPONENT_CAPACITY = 8;

Entity *entity_new() {
	Entity *self = (Entity *)malloc(sizeof(Entity));

	self->id = 0;
	self->enabled = false;
	self->destroy = false;
	//todo: GDestroyNotify function for freeing components
	self->components = darr_new(DEFAULT_COMPONENT_CAPACITY);

	self->transform = entity_addComponent(self, C_TRANSFORM);

	return self;
}

void entity_start(Entity *self) {
	self->enabled = true;
	for (int i = 0; i < self->components->size; ++i) {
		Component *c = (Component *)darr_index(self->components, i);
		component_start(c);
	}
}

void entity_update(Entity *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	for (int i = 0; i < self->components->size; ++i) {
		Component *c = (Component *)darr_index(self->components, i);
		component_update(c, dt);
	}
}

void entity_lateUpdate(Entity *self, f32 dt) {
	if (!self->enabled) {
		return;
	}

	for (int i = 0; i < self->components->size; ++i) {
		Component *c = (Component *)darr_index(self->components, i);
		component_lateUpdate(c, dt);
	}
}

void entity_render(Entity *self) {
	if (!self->enabled) {
		return;
	}
	
	for (int i = 0; i < self->components->size; ++i) {
		Component *c = (Component *)darr_index(self->components, i);
		component_render(c);
	}
}

void *entity_addComponent(Entity *self, ComponentType type) {
	Component *c = component_new(type);
	c->entity = self;
	if (self->enabled) {
		component_start(c);
	}
	darr_add(self->components, c);

	return c->component;
}

void *entity_getComponent(Entity *self, ComponentType type) {
	for (int i = 0; i < self->components->size; ++i) {
		Component *c = (Component *)darr_index(self->components, i);

		if (c->type == type) {
			return c->component;
		}
	}

	return NULL;
}

bool entity_removeComponent(Entity *self, Component *component) {
	//todo: make this safe to use while components are updating
	return darr_remove(self->components, component);
}

CLuaComponent *entity_addLua(Entity *self, const char *filename) {
	assert(self);
	void *pLuaC = entity_addComponent(self, C_LUA_COMPONENT);
	CLuaComponent *luaC = (CLuaComponent *)pLuaC;
	c_luaComponent_loadFile(luaC, filename);
	return luaC;
}
