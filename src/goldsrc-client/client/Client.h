#pragma once

#include "Common.h"
#include "Networking/SocketClient.h"
#include "Models/InfoResponse.h"
#include "Models/PlayerData.h"
#include "Parsers/ResponseParser.h"

namespace hlds
{
	class Client
	{
		static const char* INFO_REQUEST;
		static const char* PING_REQUEST;

		static const int RULES_REQUEST_ID = 0x56;
		static const int PLAYERS_REQUEST_ID = 0x55;
		static const int REQUEST_NUMBER = 0xFF;

	public:
		DLLEXPORT Client(const char* ip, short port);

	public:
		DLLEXPORT void Main();
		DLLEXPORT InfoResponse QueryInfo() const;
		DLLEXPORT RulesVector QueryRules() const;
		DLLEXPORT std::vector<PlayerData> QueryPlayers() const;
		DLLEXPORT size_t QueryPing() const;

	private:
		std::unique_ptr<char[]> GenerateRulesRequest(int authNumber, size_t& messageSize) const;
		std::unique_ptr<char[]> GeneratePlayersRequest(int authNumber, size_t& messageSize) const;
		std::unique_ptr<char[]> GenerateRequest(char type, int authNumber, size_t& messageSize) const;

	private:
		SocketClient socketClient;
		ResponseParser responseParser;

	private:
		char ip[16];
		short port;
	};
}
