#include "spritemngr.h"

SpriteMngr *spriteMngr_new() {
	SpriteMngr *self = (SpriteMngr *)malloc(sizeof(SpriteMngr));

	self->renderQueue = pqueue_new(128, sprite_getPriority);

	return self;
}

void spriteMngr_push(SpriteMngr *self, Sprite *sprite) {
	pqueue_push(self->renderQueue, sprite);
}

void spriteMngr_flush(SpriteMngr *self) {
	while (self->renderQueue->size > 0) {
		void *pSprite = pqueue_pop(self->renderQueue);
		sprite_render((Sprite *)pSprite);
	}
}

i32 sprite_getPriority(void *s1) {
	return ((Sprite *)s1)->depth;
}
