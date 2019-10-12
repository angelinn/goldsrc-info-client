#pragma once

#include <vector>
#include <string>

namespace hlds
{
	struct InfoResponse;
	struct QueryResponse;

	class ResponseParser
	{
	public:
		InfoResponse ParseInfoResponse(const char* response) const;
		int ParseAuthNumber(const char* response) const;
		std::vector<std::pair<std::string, std::string>> ParseRules(const std::vector<QueryResponse> &) const;
	};
}
