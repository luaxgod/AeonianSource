#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include "../ConsoleCol.h"

typedef std::function<void(std::vector<std::string>)> CommandFunction;

struct CommandItem {
	std::string Name;
	std::string Desc;
};


CommandItem Commands[] = {
	CommandItem { "cmds", "prints out a list of commands!"},
	CommandItem { "clicktp", "enabled/disables clicktp, use CTRL+LeftCLick to tp!"},
	CommandItem { "esp", "displays an esp on all other players in the server, good for FPS games"}
};

void runhelpcmd() {
	std::cout << igreen << "Commands: \n";
	for (CommandItem CMD : Commands) {
		std::cout << iblue << CMD.Name << white << " - " << iyellow << CMD.Desc << "\n";
	}
}
