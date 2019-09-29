#pragma once

namespace hlds
{
	class SocketClient
	{
	public:
		bool QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize, char* response);
	};
}
