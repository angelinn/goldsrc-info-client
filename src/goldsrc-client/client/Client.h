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
		static const char* CHALLENGE_REQUEST;

	public:
		DLLEXPORT void Main();
		DLLEXPORT InfoResponse QueryInfo(const char* ip, short port);
		DLLEXPORT RulesVector QueryRules(const char* ip, short port);

	private:
		std::unique_ptr<char[]> GenerateRulesRequest(int authNumber, size_t& messageSize);

	private:
		SocketClient socketClient;
		ResponseParser responseParser;
	};
}
