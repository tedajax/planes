#include "components.h"
#include "entity.h"

void *c_backgroundScroll_new(Component *super) {
	size_t bsSize = sizeof(CBackgroundScroll);
	CBackgroundScroll *self = (CBackgroundScroll *)malloc(bsSize);

	self->super = super;

	return (void *)self;
}

void c_backgroundScroll_start(void *pself) {
	C_SELF(CBackgroundScroll);

	self->speed = 50;
	self->width = 0;

	void *pSR = entity_getComponent(self->super->entity, C_SPRITE_RENDERER);
	if (pSR) {
		CSpriteRenderer *sr = (CSpriteRenderer *)pSR;
		self->width = sr->sprite->width;
	}
}

void c_backgroundScroll_update(void *pself, f32 dt) {
	C_SELF(CBackgroundScroll);
	
	CTransform *tx = self->super->entity->transform;

	tx->velocity->x = -self->speed * dt;
}

void c_backgroundScroll_lateUpdate(void *pself, f32 dt) {
	C_SELF(CBackgroundScroll);

	CTransform *tx = self->super->entity->transform;

	if (tx->position->x < self->width / 2) {
		tx->position->x += SCREEN_WIDTH + self->width;
	}
}

void c_backgroundScroll_render(void *pself) {
	
}