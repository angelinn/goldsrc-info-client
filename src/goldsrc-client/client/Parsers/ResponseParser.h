#pragma once

namespace hlds
{
	struct InfoResponse;

	class ResponseParser
	{
	public:
		InfoResponse ParseInfoResponse(const char* response) const;
		int ParseAuthNumber(const char* response) const;
	};
}
