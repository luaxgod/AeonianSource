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

void RunCommand(std::string Input);

/*Chat Hook*/

void LoadChatHook();

static void ExecuteChat() {
	do {
		if (GetKeyState(VK_RETURN) < 0 && CommandSettings::ChatHook::LastCommand.substr(0, 1) == CommandSettings::ChatHook::Prefix && CommandSettings::ChatHook::Active) {
			RunCommand(CommandSettings::ChatHook::LastCommand.substr(1, std::string::npos));

			printf("A\n");

			CommandSettings::ChatHook::LastCommand = "";

			//CommandSettings::ChatHook::KillAndWait = true;
		}
		Sleep(85);
	} while (true);
}

void LoadChatHook()
{
	do {
		if (CommandSettings::Core::Initialized && CommandSettings::ChatHook::Active) {
			r_l_getservice(RLS, "Players");
			r_l_getfield(RLS, -1, "LocalPlayer");
			r_l_getfield(RLS, -1, "PlayerGui");
			r_l_getfield(RLS, -1, "Chat");

			r_l_getfield(RLS, -1, "Frame");
			r_l_getfield(RLS, -1, "ChatBarParentFrame");
			r_l_getfield(RLS, -1, "Frame");
			r_l_getfield(RLS, -1, "BoxFrame");
			r_l_getfield(RLS, -1, "Frame");
			r_l_getfield(RLS, -1, "ChatBar");
			r_l_getfield(RLS, -1, "Text");

			std::string Command = r_l_tostring(RLS, -1);

			if (Command.substr(0, 1) == CommandSettings::ChatHook::Prefix) {
				CommandSettings::ChatHook::LastCommand = Command;
			}
		}
		Sleep(85);
	} while (true);
}



void RunCommand(std::string Input) {
	std::cout << Input << "\n";
}