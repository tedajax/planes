#include "components.h"
#include "entity.h"
#include "entitymanager.h"

void *c_playerController_new(Component *super) {
	size_t pcSize = sizeof(CPlayerController);
	CPlayerController *self = (CPlayerController *)malloc(pcSize);

	self->super = super;
	self->speed = 500;

	return (void *)self;
}

void c_playerController_start(void *pself) {
	C_SELF(CPlayerController)

	void *pSR = entity_getComponent(self->super->entity, C_SPRITE_RENDERER);
	if (pSR) {
		CSpriteRenderer *sr = (CSpriteRenderer *)pSR;
		self->width = sr->sprite->width;
		self->height = sr->sprite->height;
	}

	self->movementBounds.x = (self->width / 2) + 5;
	self->movementBounds.y = (self->height / 2) + 5;
	self->movementBounds.w = 500;
	self->movementBounds.h = 500;

	self->fireDelay = 0.2f;
	self->fireTimer = 0.0f;
}

void c_playerController_update(void *pself, f32 dt) {
	C_SELF(CPlayerController);
	_playerController_movementControls(self, dt);
	_playerController_shootControls(self, dt);
}

void _playerController_movementControls(CPlayerController *self, f32 dt) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	i32 rlDirection = 0;
	i32 udDirection = 0;

	if (input_key(SDL_SCANCODE_LEFT)) {
		--rlDirection;
	}
	if (input_key(SDL_SCANCODE_RIGHT)) {
		++rlDirection;
	}

	if (input_key(SDL_SCANCODE_UP)) {
		--udDirection;
	}
	if (input_key(SDL_SCANCODE_DOWN)) {
		++udDirection;
	}

	if (tx) {
		tx->velocity->x = rlDirection * self->speed;
		tx->velocity->y = udDirection * self->speed;
	}
}

void _playerController_shootControls(CPlayerController *self, f32 dt) {
	self->fireTimer -= dt;

	if (input_key(SDL_SCANCODE_Z) && self->fireTimer <= 0.0f) {
		self->fireTimer = self->fireDelay;

		Entity *bullet = entity_new();
		CSpriteRenderer *sr = (CSpriteRenderer *)entity_addComponent(bullet,
			C_SPRITE_RENDERER);
		sprite_setTexture(sr->sprite, "laser01_blue");
		sr->sprite->depth = -1;
		entity_addComponent(bullet, C_BULLET_CONTROLLER);

		CTransform *tx = self->super->entity->transform;
		bullet->transform->position->x = tx->position->x + sr->sprite->width / 2;
		bullet->transform->position->y = tx->position->y;

		entityManager_add(g_entities, bullet);
	}
}

void c_playerController_lateUpdate(void *pself, f32 dt) {
	C_SELF(CPlayerController)
	_playerController_checkBounds(self);
}

void _playerController_checkBounds(CPlayerController *self) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		i32 left = self->movementBounds.x;
		i32 right = self->movementBounds.x + self->movementBounds.w;
		i32 top = self->movementBounds.y;
		i32 bottom = self->movementBounds.y + self->movementBounds.h;

		if (tx->position->x < left) {
			tx->position->x = left;
		}
		if (tx->position->x > right) {
			tx->position->x = right;
		}
		if (tx->position->y < top) {
			tx->position->y = top;
		}
		if (tx->position->y > bottom) {
			tx->position->y = bottom;
		}
	}
}

void c_playerController_render(void *pself) {
	C_SELF(CPlayerController);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
	SDL_Rect boundary = {
		self->movementBounds.x - self->width / 2,
		self->movementBounds.y - self->height / 2,
		self->movementBounds.w + self->width,
		self->movementBounds.h + self->height
	};
	SDL_RenderDrawRect(g_renderer, &boundary);
}
