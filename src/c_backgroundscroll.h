#ifndef _C_BACKGROUND_SCROLL_H_
#define _C_BACKGROUND_SCROLL_H_

#include "algebra.h"

struct component_t;

typedef struct cbackground_scroll_t {
	struct component_t *super;
	f32 speed;
	i32 width;
} CBackgroundScroll;

C_DECLARE(backgroundScroll);

#endif