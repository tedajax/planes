#include "components.h"

CSpriteRenderer *c_spriteRenderer_new(Component *super) {
	CSpriteRenderer *newSR = (CSpriteRenderer *)malloc(sizeof(CSpriteRenderer));

	newSR->super = super;
	newSR->sprite = sprite_new();

	return newSR;
}

void c_spriteRenderer_start(CSpriteRenderer *self) {

}

void c_spriteRenderer_update(CSpriteRenderer *self, f32 dt) {

}

void c_spriteRenderer_lateUpdate(CSpriteRenderer *self, f32 dt) {

}

void c_spriteRenderer_render(CSpriteRenderer *self) {
	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		self->sprite->position->x = tx->position->x;
		self->sprite->position->y = tx->position->y;
		self->sprite->rotation = tx->rotation;
	}

	sprite_render(self->sprite);
}
