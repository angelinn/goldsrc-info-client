#pragma once

#include "Common.h"
#include "Networking/SocketClient.h"
#include "Models/InfoResponse.h"
#include "Parsers/ResponseParser.h"

namespace hlds
{
	class Client
	{
		static const char* INFO_REQUEST;
		static const char* RULES_CHALLENGE_REQUEST;
		static const char* PLAYERS_CHALLENGE_REQUEST;

	public:
		DLLEXPORT Client(const char* ip, short port);

	public:
		DLLEXPORT void Main();
		DLLEXPORT InfoResponse QueryInfo() const;
		DLLEXPORT RulesVector QueryRules() const;
		DLLEXPORT InfoResponse QueryPlayers() const;

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
