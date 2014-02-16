#ifndef _C_BULLET_CONTROLLER_H_
#define _C_BULLET_CONTROLLER_H_

#include "component.h"
#include "algebra.h"

typedef struct cbulletcontroller_t {
	Component *super;
	f32 speed;
	//todo; all kinds of fun parameters for bullet movement
} CBulletController;

C_DECLARE(bulletController)

#endif