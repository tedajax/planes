#include "components.h"

void *c_playerController_new(Component *super) {
	size_t pcSize = sizeof(CPlayerController);
	CPlayerController *newPC = (CPlayerController *)malloc(pcSize);

	newPC->super = super;
	newPC->speed = 500;

	return (void *)newPC;
}

void c_playerController_start(void *pself) {
	C_SELF(CPlayerController)

	self->bounds.x = 50;
	self->bounds.y = 50;
	self->bounds.w = 500;
	self->bounds.h = 400;
}

void c_playerController_update(void *pself, f32 dt) {
	C_SELF(CPlayerController);
	_playerController_movementControls(self);
}

void _playerController_movementControls(CPlayerController *self) {
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

void c_playerController_lateUpdate(void *pself, f32 dt) {
	C_SELF(CPlayerController)
	_playerController_checkBounds(self);
}

void _playerController_checkBounds(CPlayerController *self) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		i32 left = self->bounds.x;
		i32 right = self->bounds.x + self->bounds.w;
		i32 top = self->bounds.y;
		i32 bottom = self->bounds.y + self->bounds.h;

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
	SDL_RenderDrawRect(g_renderer, &self->bounds);
}
