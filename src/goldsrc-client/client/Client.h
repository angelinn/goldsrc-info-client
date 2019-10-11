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
		DLLEXPORT std::vector<std::pair<std::string, std::string>> QueryRules(const char* ip, short port);

	private:
		SocketClient socketClient;
		ResponseParser responseParser;
	};
}
