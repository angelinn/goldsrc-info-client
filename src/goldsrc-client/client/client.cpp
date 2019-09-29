#include "Client.h"
#include <cstdio>

namespace hlds
{
	const char* Client::INFO_REQUEST = "\xff\xff\xff\xffTSource Engine Query";

	void Client::Main()
	{
		printf("Hi from client dll.");
	}

	InfoResponse Client::QueryInfo(const char* ip, short port)
	{
		char response[2048];
		bool result = socketClient.QueryUDPSocket(ip, port, INFO_REQUEST, response);

		InfoResponse infoResponse = responseParser.ParseInfoResponse(response, 2048);
		return infoResponse;
	}
}
