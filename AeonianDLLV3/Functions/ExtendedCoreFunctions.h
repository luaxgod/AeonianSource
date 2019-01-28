#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "../Lua/lua.hpp"
#include "../LuaWrapper.h"

#include "AeonianFunctions.h"


int getgenv(lua_State *LS) {
	lua_pushvalue(LS, LUA_GLOBALSINDEX);
	Wrap(RLS , LS, -1);
	return 1;
}

int getreg(lua_State *LS) {
	lua_pushvalue(LS, LUA_REGISTRYINDEX);
	Wrap(RLS, LS, -1);
	return 1;
}

int getrenv(lua_State* LS) {
	lua_pushvalue(LS, int(RLS));
	Wrap(RLS, LS, -1);
	return 1;
}

int getfenv(lua_State* LS) {
	lua_pushvalue(LS, (int)LS);
	Wrap(RLS, LS, -1);
	return 1;
}


void RegisterExtendedCoreFunctions(lua_State* LS) {
	lua_register(LS, "setclipboard", Aeonian_SetClipboard);
	lua_register(LS, "toclipboard", Aeonian_SetClipboard);
	lua_register(LS, "getclipboard", Aeonian_GetClipboard);

	lua_register(LS, "getreg", getreg);
	lua_register(LS, "getrenv", getrenv);
	lua_register(LS, "getgenv", getgenv);
	lua_register(LS, "getfenv", getfenv);
}
