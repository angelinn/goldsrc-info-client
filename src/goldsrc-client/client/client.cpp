#include "Client.h"
#include "Models/QueryResponse.h"
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
		QueryResponse& response = socketClient.QueryUDPSocket(ip, port, INFO_REQUEST, strlen(INFO_REQUEST) + 1)[0];
		if (!response.response)
			throw std::runtime_error("invalid response");

		InfoResponse infoResponse = responseParser.ParseInfoResponse(response.response.get());
		return infoResponse;
	}

	std::vector<std::pair<std::string, std::string>> Client::QueryRules(const char* ip, short port)
	{
		auto responses = socketClient.QueryUDPSocket(ip, port, CHALLENGE_REQUEST, strlen(CHALLENGE_REQUEST));
		if (!responses[0].response)
			throw std::runtime_error("invalid response");

		int authNumber = responseParser.ParseAuthNumber(responses[0].response.get());
		if (authNumber == -1)
			throw std::runtime_error("invalid response");

		char rulesRequest[4 + 1 + 4];
		rulesRequest[0] = 0xff;
		rulesRequest[1] = 0xff;
		rulesRequest[2] = 0xff;
		rulesRequest[3] = 0xff;
		rulesRequest[4] = 0x56;

		char* ptrCopy = rulesRequest;
		ptrCopy += 5;

		memcpy(ptrCopy, reinterpret_cast<char *>(&authNumber), sizeof(int));

		std::vector<QueryResponse> rulesResponses = socketClient.QueryUDPSocket(ip, port, rulesRequest, 9);
		std::vector<std::pair<std::string, std::string>> rules = responseParser.ParseRules(rulesResponses);

		return rules;
	}
}
