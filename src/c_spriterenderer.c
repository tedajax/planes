#include "components.h"

void *c_spriteRenderer_new(Component *super) {
	CSpriteRenderer *newSR = (CSpriteRenderer *)malloc(sizeof(CSpriteRenderer));

	newSR->super = super;
	newSR->sprite = sprite_new();
	newSR->sprite->origin = CENTER;

	return (void *)newSR;
}

void c_spriteRenderer_start(void *pself) {

}

void c_spriteRenderer_update(void *pself, f32 dt) {

}

void c_spriteRenderer_lateUpdate(void *pself, f32 dt) {

}

void c_spriteRenderer_render(void *pself) {
	CSpriteRenderer *self = (CSpriteRenderer *)pself;

	CTransform *tx = (CTransform *)entity_getComponent(self->super->entity,
		C_TRANSFORM);

	if (tx) {
		self->sprite->position->x = tx->position->x;
		self->sprite->position->y = tx->position->y;
		self->sprite->rotation = tx->rotation;
		self->sprite->scale->x = tx->scale->x;
		self->sprite->scale->y = tx->scale->y;
	}

	spriteMngr_push(g_sprites, self->sprite);
}
