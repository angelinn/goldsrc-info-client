#include "SocketClient.h"
#include "../Models/QueryResponse.h"
#include "../Common.h"
#include "../Exceptions/SocketException.h"
#include <cstdio>
#include <winsock2.h>
#include <memory>

namespace hlds
{
	std::vector<QueryResponse> SocketClient::QueryUDPSocket(const char* ip, short port, const char* message, size_t messageSize) const
	{
		std::vector<QueryResponse> responses;

		WSADATA wsaData;
		SOCKET server = INVALID_SOCKET;
		SOCKADDR_IN address;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			ThrowSocketError("Could not initialize winsock");

		server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (server == INVALID_SOCKET)
			ThrowSocketError("Could not create socket");

		setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&TIMEOUT), sizeof(TIMEOUT));

		int slen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.S_un.S_addr = inet_addr(ip);
		address.sin_port = htons(port);

		int result = sendto(server, message, messageSize, 0, (SOCKADDR*)&address, slen);
		if (result == SOCKET_ERROR)
			ThrowSocketError("Socket error");

		char responseBuffer[PACKET_SIZE];
		memset(responseBuffer, 0, PACKET_SIZE);

		int packetMode = -1;

		do
		{
			result = recvfrom(server, responseBuffer, PACKET_SIZE, 0, (SOCKADDR*)&address, &slen);
			if (result == SOCKET_ERROR)
				ThrowSocketError("Socket error");

			responses.push_back(QueryResponse(responseBuffer, result));
		} while (result == PACKET_SIZE);

		closesocket(server);
		WSACleanup();

		return responses;
	}

	void SocketClient::ThrowSocketError(const char* message) const
	{
		std::string messageWithError(message);

		messageWithError += ", ";
		messageWithError += std::to_string(WSAGetLastError());

		throw SocketException(messageWithError.c_str());
	}
}
