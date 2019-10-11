#include "ResponseParser.h"
#include "../Models/InfoResponse.h"

namespace hlds
{
	InfoResponse ResponseParser::ParseInfoResponse(const char* response)
	{
		InfoResponse infoResponse = { 0 };

		response += 4 * sizeof(byte);

		infoResponse.header = *(reinterpret_cast<const byte *>(response));
		response += sizeof(byte);

		infoResponse.protocol = *(reinterpret_cast<const byte *>(response)) + 0;
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

		infoResponse.players = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.maxPlayers = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.bots = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.serverType = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.environment = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.visibility = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.vac = *(reinterpret_cast<const byte *>(response)) + 0;
		response += sizeof(byte);

		infoResponse.isValid = true;

		return infoResponse;
	}

}
