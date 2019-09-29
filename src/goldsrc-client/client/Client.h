#pragma once

#include "Common.h"
#include "Networking/SocketClient.h"
#include "Models/InfoResponse.h"
#include "Parsers/ResponseParser.h"

namespace hlds
{
	class Client
	{
	public:
		DLLEXPORT void Main();
		DLLEXPORT InfoResponse QueryInfo(const char* ip, short port);

	private:
		SocketClient socketClient;
		ResponseParser responseParser;
	};
}
