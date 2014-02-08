#include "planes.h"

SDL_Renderer *g_renderer = NULL;
SDL_Window *g_window = NULL;
SDL_Surface *g_screen = NULL;

const u32 SCREEN_WIDTH = 640;
const u32 SCREEN_HEIGHT = 480;

bool gameRunning;

Entity *player;

int main(int argc, char *argv[]) {
	if (!window_init()) {
		return 1;
	}

	gameRunning = true;
	SDL_Event sdlEvent;

	u32 lastTickCount = 0;

	player = entity_new(1);
	CTransform *tx = (CTransform *)entity_addComponent(player, C_TRANSFORM);
	tx->position->x = 200;
	tx->position->y = 200;
	CSpriteRenderer *sr = (CSpriteRenderer *)entity_addComponent(player,
		C_SPRITE_RENDERER);
	sprite_setTexture(sr->sprite, "ship");

	while (gameRunning) {
		while(SDL_PollEvent(&sdlEvent) != 0) {
			app_handle_event(sdlEvent);
		}

		u32 ticks = SDL_GetTicks();
		u32 delta = ticks - lastTickCount;
		f32 dt = delta / 1000.0f;
		lastTickCount = ticks;

		game_update(dt);
		game_render();
	}

	window_destroy();

	return 0;
}

void game_update(f32 dt) {
	entity_update(player, dt);

	//this should always be the last thing to update
	input_update();
}

void game_render() {
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	entity_render(player);

	SDL_RenderPresent(g_renderer);
}

bool window_init() {
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_PRINT_ERROR
		return false;
	}

	g_window = SDL_CreateWindow("Planes",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!g_window) {
		SDL_PRINT_ERROR
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (!g_renderer) {
		SDL_PRINT_ERROR
		return false;
	}

	g_screen = SDL_GetWindowSurface(g_window);

	input_init();
	textures_init();
	textures_add("ship", texture_load("assets/ship.png"));

	return true;
}

void window_destroy() {
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	input_destroy();

	SDL_Quit();
}

void app_quit() {
	gameRunning = false;
}

void app_handle_event(SDL_Event _event) {
	switch (_event.type) {
		case SDL_QUIT:
			app_quit();
			break;

		case SDL_KEYDOWN:
			if (_event.key.keysym.sym == SDLK_ESCAPE) {
				app_quit();
			}
			break;
	}
}