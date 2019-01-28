#pragma once
#include <Windows.h>

#include "../Lua/lua.hpp"

#include "AeonianFunctions.h"
#include "BitFunctions.h"
#include "CoreFunctions.h"
#include "DebugFunctions.h"
#include "ExtendedCoreFunctions.h"
#include "MiscFunctions.h"
#include "MouseAndKeyBoardFunctions.h"

void RegisterCustomFunctions(lua_State* LS) {
	RegisterMouseAndKeyBoardLibs(LS);
	RegisterDebugFunctions(LS);
	RegisterCoreFunctions(LS);
	RegisterAeonianFunctions(LS);
	RegisterExtendedCoreFunctions(LS);
	RegisterMiscFunctions(LS);
}