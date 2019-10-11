#pragma once

#include <memory>

namespace hlds
{
	class SocketClient
	{
		static const int MESSAGE_BUFFER_SIZE = 4096;

	public:
		std::unique_ptr<char[]> QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize);
	};
}
