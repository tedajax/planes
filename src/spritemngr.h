#ifndef _SPRITE_MNGR_H_
#define _SPRITE_MNGR_H_

#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "pqueue.h"
#include "sprite.h"

struct sprite_t;

typedef struct sprite_mngr_t {
	PQueue *renderQueue;
} SpriteMngr;

SpriteMngr *spriteMngr_new();
void spriteMngr_push(SpriteMngr *self, struct sprite_t *sprite);
void spriteMngr_flush(SpriteMngr *self);
void spriteMngr_renderSprite(SpriteMngr *self, struct sprite_t *sprite);

i32 sprite_getPriority(void *s1);

#endif