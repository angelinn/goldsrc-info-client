#include "Client.h"
#include <cstdio>

#include <winsock2.h>
#include "Models/InfoResponse.h"

namespace hlds
{
	char REQUEST[128] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x54, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x20, 0x45, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x20, 0x51, 0x75, 0x65, 0x72, 0x79, 0x00 };

	InfoResponse ParseResponse(const char* response, size_t size)
	{
		InfoResponse infoResponse = { 0 };

		response += 4 * sizeof(byte);

		infoResponse.header = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.protocol = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.name = std::string(response);
		response += infoResponse.name.size() + 1;

		infoResponse.map = std::string(response);
		response += infoResponse.map.size() + 1;

		infoResponse.folder = std::string(response);
		response += infoResponse.folder.size() + 1;

		infoResponse.game = std::string(response);
		response += infoResponse.game.size() + 1;

		infoResponse.appID = *(reinterpret_cast<const short *>(response));
		response += sizeof(short);

		infoResponse.players = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.maxPlayers = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.bots = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.serverType = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.environment = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.visibility = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.vac = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		return infoResponse;
	}

	void Client::Main()
	{
		printf("Hi from client dll.");

		WSADATA wsaData;
		SOCKET server = INVALID_SOCKET;
		SOCKADDR_IN address;

		printf("\nInitialising Winsock...");
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			printf("Failed.Error Code : %d", WSAGetLastError());
			return;
		}

		printf("Initialised.\n");

		server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (server == INVALID_SOCKET)
		{
			printf("Could not create socket: %d\n", WSAGetLastError());
			return;
		}

		int slen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.S_un.S_addr = inet_addr("40.115.46.129");
		address.sin_port = htons(27015);

		int result = sendto(server, REQUEST, strlen(REQUEST) + 1, 0, (SOCKADDR*)&address, slen);
		if (result == SOCKET_ERROR)
		{
			printf("socket error: %d\n", WSAGetLastError());
			return;
		}

		char buf[2048];
		memset(buf, 0, 2048);


		result = recvfrom(server, buf, 2048, 0, (SOCKADDR*)&address, &slen);
		if (result == SOCKET_ERROR)
		{
			printf("socket error: %d\n", WSAGetLastError());
			return;
		}

		InfoResponse infoResponse = ParseResponse(buf, 2048);

		closesocket(server);
		WSACleanup();
	}
}
