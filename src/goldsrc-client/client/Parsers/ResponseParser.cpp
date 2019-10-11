#include "ResponseParser.h"
#include "../Models/InfoResponse.h"

namespace hlds
{
	InfoResponse ResponseParser::ParseInfoResponse(const char* response) const
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

	int ResponseParser::ParseAuthNumber(const char* response) const
	{
		response += 4 * sizeof(byte);
		if (*response != 0x41)
			return -1;

		++response;
		int authNumber = 0;
		memcpy(&authNumber, response, sizeof(int));

		return authNumber;
	}

	std::vector<std::pair<std::string, std::string>> ResponseParser::ParseRules(const char* response) const
	{
		response += 14;
		short rulesNumber = 0;
		memcpy(&rulesNumber, response, sizeof(short));

		response += sizeof(int);

		std::vector<std::pair<std::string, std::string>> rules;
		for (int i = 0; i < rulesNumber; ++i)
		{
			std::string rule = std::string(response);
			response += rule.size() + 1;

			std::string value = std::string(response);
			response += value.size() + 1;

			rules.push_back(std::make_pair(rule, value));
		}

		return std::move(rules);
	}
}
