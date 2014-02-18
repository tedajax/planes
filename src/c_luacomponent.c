#include "components.h"
#include "entity.h"

void *c_luaComponent_new(Component *super) {
	size_t lcSize = sizeof(CLuaComponent);
	CLuaComponent *self = (CLuaComponent * )malloc(lcSize);

	self->super = super;
	self->fileLoaded = false;
	self->filename = NULL;
	self->L = lua_open();
	luaL_openlibs(self->L);

	self->bindTable = g_hash_table_new_full(g_str_hash,
		g_str_equal,
		NULL,
		luaBind_free);

	return (void *)self;
}

void c_luaComponent_start(void *pself) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	LuaBind *testBind = luaBind_new("tryShoot", 0);
	c_luaComponent_bind(self, testBind);

	lua_getglobal(self->L, "start");
	if (lua_pcall(self->L, 0, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_update(void *pself, f32 dt) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}	

	if (input_key(SDL_SCANCODE_A)) {
		c_luaComponent_call(self, "tryShoot");
	}

	lua_getglobal(self->L, "update");
	lua_pushnumber(self->L, dt);
	if (lua_pcall(self->L, 1, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_lateUpdate(void *pself, f32 dt) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	lua_getglobal(self->L, "lateUpdate");
	lua_pushnumber(self->L, dt);
	if (lua_pcall(self->L, 1, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_render(void *pself) {
	C_SELF(CLuaComponent)

	if (!self->fileLoaded) {
		return;
	}

	lua_getglobal(self->L, "render");
	if (lua_pcall(self->L, 0, 0, 0) != 0) {
		LUA_ERROR(self->L)
	}
}

void c_luaComponent_loadFile(CLuaComponent *self, const char *filename) {
	self->filename = (char *)realloc(self->filename, strlen(filename));
	strcpy(self->filename, filename);
	luaL_dofile(self->L, filename);
	self->fileLoaded = true;
}

void c_luaComponent_reload(CLuaComponent *self) {
	if (!self->fileLoaded) {
		return;
	}
	
	lua_close(self->L);
	self->L = lua_open();
	luaL_openlibs(self->L);
	luaL_dofile(self->L, self->filename);
}

void c_luaComponent_call(CLuaComponent *self, const char *function, ...) {
	if (!self->fileLoaded) {
		return;
	}

	LuaBind *bind = g_hash_table_lookup(self->bindTable,
		(gconstpointer)function);

	if (bind) {
		va_list argv;
		va_start(argv, function);

		luaBind_callv(bind, self->L, argv);

		va_end(argv);
	}
}

void c_luaComponent_bind(CLuaComponent *self, LuaBind *bind) {
	assert(self && bind);

	g_hash_table_insert(self->bindTable, (gpointer)bind->funcName, bind);
}
