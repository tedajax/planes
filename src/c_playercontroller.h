#ifndef _C_PLAYER_CONTROLLER_H_
#define _C_PLAYER_CONTROLLER_H_

#include "algebra.h"

struct component_t;

typedef struct cplayer_controller_t {
	struct component_t *super;
	f32 speed;
} CPlayerController;

CPlayerController *c_playerController_new(struct component_t *super);
void c_playerController_start(CPlayerController *self);
void c_playerController_update(CPlayerController *self, f32 dt);
void c_playerController_lateUpdate(CPlayerController *self, f32 dt);
void c_playerController_render(CPlayerController *self);

#endif