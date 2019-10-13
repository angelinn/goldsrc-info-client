
#include <iostream>
#include "../client/Client.h"

int main()
{
	try
	{
		hlds::Client client("40.115.46.129", 27015);

		hlds::InfoResponse info = client.QueryInfo();
		std::cout << info.name << ", " << info.game << ", " << info.map << ", " << info.players << " / " << info.maxPlayers << std::endl;

		auto rules = client.QueryRules();
		for (auto& rule : rules)
			std::cout << rule.first << " = " << rule.second << std::endl;

		size_t ping = client.QueryPing();
		std::cout << "Ping: " << ping << std::endl;

		std::vector<hlds::PlayerData> players = client.QueryPlayers();
		std::cout << "Players count: " << players.size() << std::endl;

		for (auto& player : players)
			std::cout << "[" << player.index << "] " << player.name << ", " << player.score << " frags, " << player.duration << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
