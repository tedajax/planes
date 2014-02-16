#include "entitymanager.h"
#include "entity.h"

EntityManager *entityManager_new() {
	EntityManager *self = (EntityManager * )malloc(sizeof(EntityManager));

	self->currentId = 1;
	self->addMode = IMMEDIATE;
	self->entities = g_ptr_array_sized_new(128);
	self->addQueue = g_queue_new();
	self->removeQueue = g_queue_new();

	return self;
}

void entityManager_start(EntityManager *self) {
	for (int i = 0; i < self->entities->len; ++i) {
		Entity *e = (Entity *)g_ptr_array_index(self->entities, i);
		if (e) {
			entity_start(e);
		}
	}

	self->addMode = QUEUED;
}

void entityManager_update(EntityManager *self, f32 dt) {
	for (int i = 0; i < self->entities->len; ++i) {
		Entity *e = (Entity *)g_ptr_array_index(self->entities, i);
		if (e) {
			entity_update(e, dt);
		}
	}

	for (int i = 0; i < self->entities->len; ++i) {
		Entity *e = (Entity *)g_ptr_array_index(self->entities, i);
		if (e) {
			entity_lateUpdate(e, dt);

			if (e->destroy) {
				g_queue_push_tail(self->removeQueue, e);
			}
		}
	}

	void *ptrEntity = g_queue_pop_head(self->removeQueue);
	while (ptrEntity != NULL) {
		g_ptr_array_remove(self->entities, ptrEntity);
		ptrEntity = g_queue_pop_head(self->removeQueue);
	}

	void *ptrAddEntity = g_queue_pop_head(self->addQueue);
	while (ptrAddEntity != NULL) {
		g_ptr_array_add(self->entities, ptrAddEntity);
		entity_start((Entity *)ptrAddEntity);
		ptrAddEntity = g_queue_pop_head(self->addQueue);
	}
}

void entityManager_render(EntityManager *self) {
	for (int i = 0; i < self->entities->len; ++i) {
		Entity *e = (Entity *)g_ptr_array_index(self->entities, i);
		if (e) {
			entity_render(e);
		}
	}
}


void entityManager_add(EntityManager *self, Entity *entity) {
	if (self->addMode == IMMEDIATE) {
		g_ptr_array_add(self->entities, entity);
		entity_start(entity);
	} else {
		g_queue_push_tail(self->addQueue, entity);
	}
}
