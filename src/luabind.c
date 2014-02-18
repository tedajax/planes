#include "luabind.h"

LuaBind *luaBind_new(const char *fname, int argc, ...) {
	LuaBind *self = (LuaBind *)malloc(sizeof(LuaBind));

	self->funcName = (char *)malloc(strlen(fname));
	strcpy(self->funcName, fname);
	self->argc = argc;
	
	self->argt = (LuaBindArgTypes *)malloc(sizeof(LuaBindArgTypes) * argc);

	va_list argv;
	va_start(argv, argc);

	for (int i = 0; i < argc; ++i) {
		int type = va_arg(argv, int);
		self->argt[i] = (LuaBindArgTypes)type;
	}

	va_end(argv);

	return self;
}

void luaBind_call(LuaBind *self, lua_State *L, ...) {
	assert(self && L);

	va_list argv;
	va_start(argv, L);

	luaBind_callv(self, L, argv);

	va_end(argv);
}

void luaBind_callv(LuaBind *self, lua_State *L, va_list argv) {
	assert(self && L);

	lua_getglobal(L, self->funcName);

	for (int i = 0; i < self->argc; ++i) {
		LuaBindArgTypes t = self->argt[i];
		switch (t) {
			case LUA_ARG_BOOLEAN: {
				int boolArg = va_arg(argv, int);
				lua_pushboolean(L, boolArg);
				break;
			}

			case LUA_ARG_INTEGER: {
				int intArg = va_arg(argv, int);
				lua_pushinteger(L, intArg);
				break;
			}

			case LUA_ARG_FLOAT: {
				float floatArg = va_arg(argv, double);
				lua_pushnumber(L, floatArg);
				break;
			}

			case LUA_ARG_STRING: {
				char *stringArg = va_arg(argv, char *);
				lua_pushstring(L, stringArg);
				break;
			}
		}
	}

	if (lua_pcall(L, self->argc, 0, 0) != 0) {
		LUA_ERROR(L);
	}
}

void luaBind_free(void *pself) {
	LuaBind *self = (LuaBind *)pself;
	free(self->funcName);
	free(self->argt);
	free(self);
}