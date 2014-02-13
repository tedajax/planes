#include "components.h"

void *c_playerController_new(Component *super) {
	size_t pcSize = sizeof(CPlayerController);
	CPlayerController *newPC = (CPlayerController *)malloc(pcSize);

	newPC->super = super;
	newPC->speed = 500;

	return (void *)newPC;
}

void c_playerController_start(void *pself) {

}

void c_playerController_update(void *pself, f32 dt) {
	CPlayerController *self = (CPlayerController *)pself;

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

}

void c_playerController_render(void *pself) {

}
