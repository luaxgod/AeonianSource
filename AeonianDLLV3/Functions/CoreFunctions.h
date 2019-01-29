#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "../Lua/lua.hpp"
#include "../LuaWrapper.h"



int GetRawMetaTable(lua_State *LS) {
	if (lua_gettop(LS) == 0) {
		luaL_error(LS, "'getrawmetatable' needs 1 argument.");
		return 0;
	}
	UnWrap(LS, RLS, 1);
	if (r_l_getmetatable(RLS, -1) == 0) {
		lua_pushnil(LS);
		return 0;
	}
	Wrap(RLS, LS, -1);
	return 1;
}

int SetRawMetaTable(lua_State* LS) {
	if (lua_gettop(LS) == 0) {
		luaL_error(LS, "'setrawmetatable' needs at least 1 argument.");
		return 0;
	}
	r_l_pushboolean(RLS, r_l_setmetatable(RLS, 1));
	return 1;
}

int LoadStringI(lua_State* LS) {
	if (lua_gettop(LS) == 0) {
		luaL_error(LS, "'loadstring' needs 1 string argument.");
		return 0;
	}
	Wrapper::Execute_Script(std::string(lua_tostring(LS, -1)));
	return 0;
}


void RegisterCoreFunctions(lua_State* LS) {
	lua_register(LS, "getrawmetatable", GetRawMetaTable);
	lua_register(LS, "setrawmetatable", GetRawMetaTable);
	lua_register(LS, "loadstring", LoadStringI);
}
