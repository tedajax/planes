#ifndef _C_LUA_COMPONENT_H_
#define _C_LUA_COMPONENT_H_

#include <stdbool.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <luajit.h>
#include <lauxlib.h>

#include "component.h"

typedef struct clua_component_t {
	struct component_t *super;
	bool fileLoaded;
	char *filename;
	lua_State *L;
} CLuaComponent;

C_DECLARE(luaComponent);

void c_luaComponent_loadFile(CLuaComponent *self, const char *filename);

#define LUA_ERROR(L) fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));

#endif
