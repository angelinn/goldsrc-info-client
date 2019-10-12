#pragma once

#include <memory>
#include <vector>

namespace hlds
{
	struct QueryResponse;

	class SocketClient
	{
		static const int MESSAGE_BUFFER_SIZE = 1400;

	public:
		std::vector<QueryResponse> QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize);
	};
}
