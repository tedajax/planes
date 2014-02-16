#ifndef _C_PLAYER_CONTROLLER_H_
#define _C_PLAYER_CONTROLLER_H_

#include "algebra.h"

#include <SDL2/SDL.h>

struct component_t;

typedef struct cplayer_controller_t {
	struct component_t *super;
	f32 speed;
	i32 width;
	i32 height;
	SDL_Rect movementBounds;

	f32 fireDelay;
	f32 fireTimer;
} CPlayerController;

C_DECLARE(playerController);

void _playerController_movementControls(CPlayerController *self, f32 dt);
void _playerController_shootControls(CPlayerController *self, f32 dt);
void _playerController_checkBounds(CPlayerController *self);

#endif