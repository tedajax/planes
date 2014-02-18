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