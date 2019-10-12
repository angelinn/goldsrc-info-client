#pragma once

#include <vector>
#include <string>

namespace hlds
{
	struct InfoResponse;
	struct QueryResponse;

	class ResponseParser
	{
		static const int FIRST_PACKET_HEADER_BYTES = 14;
		static const int N_PACKET_HEADER_BYTES = 9;
		static const size_t RULES_COUNT_SIZE = sizeof(short);

	public:
		InfoResponse ParseInfoResponse(const char* response) const;
		int ParseAuthNumber(const char* response) const;
		std::vector<std::pair<std::string, std::string>> ParseRules(const std::vector<QueryResponse> &) const;
	};
}
