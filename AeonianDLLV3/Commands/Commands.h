#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "../Offsets.h"

/*Command Settings*/

namespace CommandSettings
{
	namespace Core {
		static bool Initialized;
	}
	namespace ChatHook
	{
		static bool Active;
		static std::string Prefix = ";";
		static std::string LastCommand = "";
	}
}

void RunCommand(std::string Input) {
	std::cout << Input << "\n";
}
