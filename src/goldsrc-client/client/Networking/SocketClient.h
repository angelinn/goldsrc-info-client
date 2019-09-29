#pragma once

namespace hlds
{
	class SocketClient
	{
	public:
		bool QueryUDPSocket(const char* ip, short port, const char* message, char* response);
	};
}
