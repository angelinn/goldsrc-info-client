#pragma once

#include <memory>

namespace hlds
{
	class SocketClient
	{
	public:
		std::unique_ptr<char> QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize);
	};
}
