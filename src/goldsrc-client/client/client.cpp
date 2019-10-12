#include "Client.h"
#include "Models/QueryResponse.h"
#include <cstdio>

namespace hlds
{
	const char* Client::INFO_REQUEST = "\xff\xff\xff\xffTSource Engine Query\0";
	const char* Client::RULES_CHALLENGE_REQUEST = "\xff\xff\xff\xffV\xff\xff\xff\xff";
	const char* Client::PLAYERS_CHALLENGE_REQUEST = "\xff\xff\xff\xffU\xff\xff\xff\xff";

	void Client::Main()
	{
		printf("Hi from client dll.");
	}

	Client::Client(const char* ip, short port)
	{
		strcpy(this->ip, ip);
		this->port = port;
	}

	InfoResponse Client::QueryInfo() const
	{
		QueryResponse& response = socketClient.QueryUDPSocket(ip, port, INFO_REQUEST, strlen(INFO_REQUEST) + 1)[0];
		if (!response.response)
			throw std::runtime_error("invalid response");

		InfoResponse infoResponse = responseParser.ParseInfoResponse(response.response.get());
		return infoResponse;
	}

	RulesVector Client::QueryRules() const
	{
		std::vector<QueryResponse> responses = socketClient.QueryUDPSocket(ip, port, RULES_CHALLENGE_REQUEST, strlen(RULES_CHALLENGE_REQUEST));
		if (!responses[0].response)
			throw std::runtime_error("invalid response");

		int authNumber = responseParser.ParseAuthNumber(responses[0].response.get());
		if (authNumber == -1)
			throw std::runtime_error("invalid response");

		size_t rulesRequestSize = 0;
		std::unique_ptr<char[]> rulesRequest = GenerateRulesRequest(authNumber, rulesRequestSize);

		std::vector<QueryResponse> rulesResponses = socketClient.QueryUDPSocket(ip, port, rulesRequest.get(), rulesRequestSize);
		RulesVector rules = responseParser.ParseRules(rulesResponses);

		return rules;
	}

	InfoResponse Client::QueryPlayers() const
	{
		std::vector<QueryResponse> responses = socketClient.QueryUDPSocket(ip, port, PLAYERS_CHALLENGE_REQUEST, strlen(PLAYERS_CHALLENGE_REQUEST));
		if (!responses[0].response)
			throw std::runtime_error("invalid response");

		int authNumber = responseParser.ParseAuthNumber(responses[0].response.get());
		if (authNumber == -1)
			throw std::runtime_error("invalid response");

		size_t rulesRequestSize = 0;
		std::unique_ptr<char[]> playersRequest = GeneratePlayersRequest(authNumber, rulesRequestSize);

		std::vector<QueryResponse> playerResponses = socketClient.QueryUDPSocket(ip, port, playersRequest.get(), rulesRequestSize);
		char* ptr = playerResponses[0].response.get();

		return InfoResponse();
	}

	std::unique_ptr<char[]> Client::GenerateRulesRequest(int authNumber, size_t& messageSize) const
	{
		return GenerateRequest(0x56, authNumber, messageSize);
	}

	std::unique_ptr<char[]> Client::GeneratePlayersRequest(int authNumber, size_t& messageSize) const
	{
		return GenerateRequest(0x55, authNumber, messageSize);
	}

	std::unique_ptr<char[]> Client::GenerateRequest(char type, int authNumber, size_t& messageSize) const
	{
		messageSize = 4 + 1 + 4;

		std::unique_ptr<char[]> rulesRequest = std::make_unique<char[]>(messageSize);
		rulesRequest[0] = 0xff;
		rulesRequest[1] = 0xff;
		rulesRequest[2] = 0xff;
		rulesRequest[3] = 0xff;
		rulesRequest[4] = type;

		memcpy(rulesRequest.get() + 5, reinterpret_cast<char *>(&authNumber), sizeof(int));
		return rulesRequest;
	}
}
