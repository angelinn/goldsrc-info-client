#pragma once

namespace hlds
{
	struct InfoResponse;

	class ResponseParser
	{
	public:
		InfoResponse ParseInfoResponse(const char* response, size_t size);
	};
}
