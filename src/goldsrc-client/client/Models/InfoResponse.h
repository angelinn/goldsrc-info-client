#pragma once

#include <string>

namespace hlds
{
	typedef unsigned char byte;

	struct InfoResponse
	{
		byte header;
		int protocol;
		std::string name;
		std::string map;
		std::string folder;
		std::string game;
		short appID;
		int players;
		int maxPlayers;
		int bots;
		int serverType;
		int environment;
		int visibility;
		int vac;
	};
}
