#include "spritemngr.h"

SpriteMngr *spriteMngr_new() {
	SpriteMngr *self = (SpriteMngr *)malloc(sizeof(SpriteMngr));

	self->renderQueue = pqueue_new(64, sprite_getPriority);

	return self;
}

void spriteMngr_push(SpriteMngr *self, Sprite *sprite) {
	pqueue_push(self->renderQueue, sprite);
}

void spriteMngr_flush(SpriteMngr *self) {
	while (self->renderQueue->size > 0) {
		void *pSprite = pqueue_pop(self->renderQueue);
		spriteMngr_renderSprite(self, (Sprite *)pSprite);
	}
}

void spriteMngr_renderSprite(SpriteMngr *self, Sprite *sprite) {
	sprite_render(sprite);
}

i32 sprite_getPriority(void *s1) {
	return ((Sprite *)s1)->depth;
}
