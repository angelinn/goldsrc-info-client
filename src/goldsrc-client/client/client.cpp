#include "Client.h"
#include <cstdio>

namespace hlds
{
	const char* Client::INFO_REQUEST = "\xff\xff\xff\xffTSource Engine Query\0";
	const char* Client::CHALLENGE_REQUEST = "\xff\xff\xff\xffV\xff\xff\xff\xff";

	void Client::Main()
	{
		printf("Hi from client dll.");
	}

	InfoResponse Client::QueryInfo(const char* ip, short port)
	{
		std::unique_ptr<char> response = socketClient.QueryUDPSocket(ip, port, INFO_REQUEST, strlen(INFO_REQUEST) + 1);
		if (!response)
			throw std::runtime_error("invalid response");
		
		InfoResponse infoResponse = responseParser.ParseInfoResponse(response.get());
		return infoResponse;
	}

	InfoResponse Client::QueryRules(const char* ip, short port)
	{
		std::unique_ptr<char> response = socketClient.QueryUDPSocket(ip, port, CHALLENGE_REQUEST, strlen(CHALLENGE_REQUEST));
		if (!response)
			throw std::runtime_error("invalid response");

		InfoResponse infoResponse = responseParser.ParseInfoResponse(response.get());
		return infoResponse;
	}
}
