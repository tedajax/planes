#include "planes.h"

SDL_Renderer *g_renderer = NULL;
SDL_Window *g_window = NULL;
SDL_Surface *g_screen = NULL;
EntityManager *g_entities = NULL;
SpriteMngr *g_sprites = NULL;
time_t g_randomSeed = 0;

const u32 SCREEN_WIDTH = 1280;
const u32 SCREEN_HEIGHT = 720;

bool gameRunning;

int main(int argc, char *argv[]) {
	if (!window_init()) {
		return 1;
	}

	gameRunning = true;
	SDL_Event sdlEvent;

	u32 lastTickCount = 0;

	g_entities = entityManager_new();
	g_sprites = spriteMngr_new();

	do {
		Entity *player = entity_new();
		CTransform *tx = player->transform;
		tx->position->x = 200;
		tx->position->y = SCREEN_HEIGHT / 2;
		CSpriteRenderer *sr = (CSpriteRenderer *)entity_addComponent(player,
			C_SPRITE_RENDERER);
		entity_addComponent(player, C_PLAYER_CONTROLLER);
		sprite_setTexture(sr->sprite, "pship3_blue");
		entityManager_add(g_entities, player);
	} while(0);

	do {
		Entity *stars = entity_new();
		CTransform *tx = stars->transform;
		tx->position->x = 1000;
		tx->position->y = SCREEN_HEIGHT / 2;
		CSpriteRenderer *sr = (CSpriteRenderer *)entity_addComponent(stars,
			C_SPRITE_RENDERER);
		sprite_setTexture(sr->sprite, "pship3_red");
		entity_addLua(stars, "scripts/background.lua");
		entityManager_add(g_entities, stars);
	} while(0);
	
	

	entityManager_start(g_entities);

	u32 secondCounter = 0;
	u32 framesCounted = 0;

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

		++framesCounted;
		secondCounter += delta;

		if (secondCounter >= 1000) {
			printf("FPS: %d\n", framesCounted);
			secondCounter -= 1000;
			framesCounted = 0;
		}
	}

	window_destroy();

	return 0;
}

void game_update(f32 dt) {
	entityManager_update(g_entities, dt);

	if (input_keyDown(SDL_SCANCODE_R)) {
		entityManager_reloadLua(g_entities);
	}

	//this should always be the last thing to update
	input_update();
}

void game_render() {
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	entityManager_render(g_entities);
	spriteMngr_flush(g_sprites);

	SDL_RenderPresent(g_renderer);
}

bool window_init() {
	g_randomSeed = time(NULL);
	srand(g_randomSeed);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_PRINT_ERROR
		return false;
	}

	g_window = SDL_CreateWindow("Planes",
		0, //SDL_WINDOWPOS_UNDEFINED,
		16, //SDL_WINDOWPOS_UNDEFINED,
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

	ResourceMap *rmap = resourceMap_new("assets/images.rmap");
	resourceMap_load(rmap);
	textures_loadRMap(rmap);
	resourceMap_free(rmap);

	components_initialize();

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
