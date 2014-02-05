#include "input.h"

u8 *oldKeystates = NULL;
u8 *newKeystates = NULL;

void input_init() {
	assert(oldKeystates == NULL && newKeystates == NULL);

	oldKeystates = (u8 *)calloc(SDL_NUM_SCANCODES, sizeof(u8));
	newKeystates = (u8 *)calloc(SDL_NUM_SCANCODES, sizeof(u8));
}

void input_update() {
	assert(oldKeystates != NULL && newKeystates != NULL);

	for (u32 i = 0; i < SDL_NUM_SCANCODES; ++i) {
		oldKeystates[i] = newKeystates[i];
	}

	const u8 *keys = SDL_GetKeyboardState(NULL);
	for (u32 i = 0; i < SDL_NUM_SCANCODES; ++i) {
		newKeystates[i] = keys[i];
	}
}

void input_destroy() {
	assert(oldKeystates != NULL && newKeystates != NULL);

	newKeystates = NULL;
	free(oldKeystates);
}

bool input_validKey(u32 scancode) {
	if (scancode >= SDL_NUM_SCANCODES) {
		return false;
	}
	return true;
}

bool input_key(u32 scancode) {
	if (!input_validKey(scancode)) {
		return false;
	}

	return newKeystates[scancode];
}

bool input_keyDown(u32 scancode) {
	if (!input_validKey(scancode)) {
		return false;
	}

	return newKeystates[scancode] && !oldKeystates[scancode];
}

bool input_keyUp(u32 scancode) {
	if (!input_validKey(scancode)) {
		return false;
	}

	return !newKeystates[scancode] && oldKeystates[scancode];
}