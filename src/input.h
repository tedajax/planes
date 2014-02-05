#ifndef _INPUT_H_
#define _INPUT_H_

#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "types.h"

u8 *oldKeystates;
u8 *newKeystates;

void input_init();
void input_update();
void input_destroy();

bool input_validKey(u32 scancode);
bool input_key(u32 scancode);
bool input_keyDown(u32 scancode);
bool input_keyUp(u32 scancode);

#endif