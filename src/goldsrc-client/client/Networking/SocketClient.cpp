#include "SocketClient.h"
#include <cstdio>
#include <winsock2.h>
#include <memory>

namespace hlds
{
	std::unique_ptr<char> SocketClient::QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize)
	{
		WSADATA wsaData;
		SOCKET server = INVALID_SOCKET;
		SOCKADDR_IN address;

		printf("\nInitialising Winsock...");
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			printf("Failed.Error Code : %d", WSAGetLastError());
			return false;
		}

		printf("Initialised.\n");

		server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (server == INVALID_SOCKET)
		{
			printf("Could not create socket: %d\n", WSAGetLastError());
			return false;
		}

		int slen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.S_un.S_addr = inet_addr(ip);
		address.sin_port = htons(port);

		int result = sendto(server, message, messageSize, 0, (SOCKADDR*)&address, slen);
		if (result == SOCKET_ERROR)
		{
			printf("socket error: %d\n", WSAGetLastError());
			return false;
		}

		char buf[2048];
		memset(buf, 0, 2048);

		result = recvfrom(server, buf, 2048, 0, (SOCKADDR*)&address, &slen);
		if (result == SOCKET_ERROR)
		{
			printf("socket error: %d\n", WSAGetLastError());
			return false;
		}

		closesocket(server);
		WSACleanup();

		std::unique_ptr<char> responsePtr = std::make_unique<char>(result);
		memcpy(responsePtr.get(), buf, result);

		return responsePtr;
	}
}
