#include "entitymanager.h"
#include "entity.h"

EntityManager *entityManager_new() {
	EntityManager *self = (EntityManager * )malloc(sizeof(EntityManager));

	self->currentId = 1;
	self->addMode = IMMEDIATE;
	self->entities = dynArr_new(128);
	self->addQueue = g_queue_new();
	self->removeQueue = g_queue_new();

	return self;
}

void entityManager_start(EntityManager *self) {
	for (int i = 0; i < self->entities->size; ++i) {
		Entity *e = (Entity *)dynArr_index(self->entities, i);
		if (e) {
			entity_start(e);
		}
	}

	self->addMode = QUEUED;
}

void entityManager_update(EntityManager *self, f32 dt) {
	for (int i = 0; i < self->entities->size; ++i) {
		Entity *e = (Entity *)dynArr_index(self->entities, i);
		if (e) {
			entity_update(e, dt);
		}
	}

	for (int i = 0; i < self->entities->size; ++i) {
		Entity *e = (Entity *)dynArr_index(self->entities, i);
		if (e) {
			entity_lateUpdate(e, dt);

			if (e->destroy) {
				g_queue_push_tail(self->removeQueue, e);
			}
		}
	}

	void *ptrEntity = g_queue_pop_head(self->removeQueue);
	while (ptrEntity != NULL) {
		dynArr_remove(self->entities, ptrEntity);
		ptrEntity = g_queue_pop_head(self->removeQueue);
	}

	void *ptrAddEntity = g_queue_pop_head(self->addQueue);
	while (ptrAddEntity != NULL) {
		_entityManager_addEntity(self, (Entity *)ptrAddEntity);
		ptrAddEntity = g_queue_pop_head(self->addQueue);
	}
}

void entityManager_render(EntityManager *self) {
	for (int i = 0; i < self->entities->size; ++i) {
		Entity *e = (Entity *)dynArr_index(self->entities, i);
		if (e) {
			entity_render(e);
		}
	}
}

void entityManager_add(EntityManager *self, Entity *entity) {
	if (self->addMode == IMMEDIATE) {
		_entityManager_addEntity(self, entity);	
	} else {
		g_queue_push_tail(self->addQueue, entity);
	}
}

void _entityManager_addEntity(EntityManager *self, struct entity_t *entity) {
	if (entity->id <= 0) {
		entity->id = self->currentId++;
	}
	dynArr_add(self->entities, entity);
	if (self->addMode == QUEUED) {
		entity_start(entity);
	}
}

void entityManager_reloadLua(EntityManager *self) {
	assert(self);

	for (int i = 0; i < self->entities->size; ++i) {
		Entity *e = (Entity *)dynArr_index(self->entities, i);
		if (e) {
			void *pLua = entity_getComponent(e, C_LUA_COMPONENT);
			if (pLua) {
				CLuaComponent *lua = (CLuaComponent *)pLua;
				c_luaComponent_reload(lua);
			}
		}
	}
}
