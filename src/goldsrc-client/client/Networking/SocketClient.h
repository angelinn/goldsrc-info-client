#pragma once

#include <memory>
#include <vector>

namespace hlds
{
	struct QueryResponse;

	class SocketClient
	{
		static const int TIMEOUT = 2000;

	public:
		std::vector<QueryResponse> QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize) const;
	};
}
