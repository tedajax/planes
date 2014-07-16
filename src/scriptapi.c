#include "scriptapi.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "resourcemap.h"
#include "types.h"
#include "input.h"
#include "textures.h"
#include "sprite.h"
#include "entity.h"
#include "components.h"
#include "entitymanager.h"
#include "spritemngr.h"

#include "globals.h"

void spawnBullet(float x, float y, float angle) {
	Entity *bullet = entity_new();
	CTransform *tx = bullet->transform;
	tx->position->x = x;
	tx->position->y = y;
	tx->rotation = angle;
	CSpriteRenderer *sr = (CSpriteRenderer *)entity_addComponent(bullet,
		C_SPRITE_RENDERER);
	entity_addComponent(bullet, C_BULLET_CONTROLLER);
	sprite_setTexture(sr->sprite, "laser16_red");

	entityManager_add(g_entities, bullet);
}

Entity *getEntity(int id) {
	return entityManager_get(g_entities, id);
}

void entitySetPosition(Entity *e, float x, float y) {
	assert(e);
	e->transform->position->x = x;
	e->transform->position->y = y;
}

void entitySetRotation(Entity *e, float r) {
	assert(e);
	e->transform->rotation = r;
}

void entitySetScale(Entity *e, float x, float y) {
	assert(e);
	e->transform->scale->x = x;
	e->transform->scale->y = y;
}

void entitySetVelocity(Entity *e, float x, float y) {
	assert(e);
	e->transform->velocity->y = y;
	e->transform->velocity->x = x;
}

void entitySetAngularVelocity(Entity *e, float r) {
	assert(e);
	e->transform->angularVelocity = r;
}

Sprite *entityGetSprite(Entity *e) {
	assert(e);
	void *pSR = entity_getComponent(e, C_SPRITE_RENDERER);
	if (pSR) {
		CSpriteRenderer *sr = (CSpriteRenderer *)pSR;
		return sr->sprite;
	}
	return NULL;
}

int random_int(int min, int max) {
	return (rand() % (max - min)) + min;
}