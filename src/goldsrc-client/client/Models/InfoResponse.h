#pragma once

#include <string>

namespace hlds
{
	typedef unsigned char byte;

	struct InfoResponse
	{
		byte header;
		byte protocol;
		std::string name;
		std::string map;
		std::string folder;
		std::string game;
		short appID;
		byte players;
		byte maxPlayers;
		byte bots;
		byte serverType;
		byte environment;
		byte visibility;
		byte vac;
	};
}
