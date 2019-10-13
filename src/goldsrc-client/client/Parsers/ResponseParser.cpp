#include "ResponseParser.h"
#include "../Models/InfoResponse.h"
#include "../Models/QueryResponse.h"
#include "../Models/PlayerData.h"
#include "../Common.h"

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

	RulesVector ResponseParser::ParseRules(const std::vector<QueryResponse>& responses) const
	{
		size_t baseSize = responses[0].size - FIRST_PACKET_HEADER_BYTES + RULES_COUNT_SIZE;

		char* iterator = responses[0].response.get();
		iterator += FIRST_PACKET_HEADER_BYTES;
		short rulesNumber = 0;
		memcpy(&rulesNumber, iterator, RULES_COUNT_SIZE);

		iterator += RULES_COUNT_SIZE;

		std::unique_ptr<char[]> response = std::make_unique<char[]>(PACKET_SIZE * responses.size());
		memcpy(response.get(), iterator, baseSize);

		size_t copySize = 0;
		iterator = nullptr;

		for (int i = 1; i < responses.size(); ++i)
		{
			copySize = responses[i].size - N_PACKET_HEADER_BYTES;
			iterator = responses[i].response.get();
			iterator += N_PACKET_HEADER_BYTES;

			memcpy(response.get() + baseSize, iterator, copySize);
		}

		iterator = response.get();

		RulesVector rules;
		for (int i = 0; i < rulesNumber; ++i)
		{
			std::string rule = std::string(iterator);
			iterator += rule.size() + 1;

			std::string value = std::string(iterator);
			iterator += value.size() + 1;

			rules.push_back(std::make_pair(rule, value));
		}

		return std::move(rules);
	}

	std::vector<PlayerData> ResponseParser::ParsePlayers(const QueryResponse& response) const
	{
		const char* iterator = response.response.get();
		iterator += sizeof(int);
		char id = *iterator;

		if (id != 0x44)
			throw std::runtime_error("wrong request");

		++iterator;
		int playersCount = *iterator;
		++iterator;

		std::vector<PlayerData> players;

		for (int i = 0; i < playersCount; ++i)
		{
			PlayerData player = { 0 };
			player.index = *iterator;
			++iterator;

			player.name = std::string(iterator);
			iterator += player.name.size() + 1;

			memcpy(&player.score, iterator, sizeof(long));
			iterator += sizeof(long);

			memcpy(&player.duration, iterator, sizeof(float));

			players.push_back(std::move(player));
		}

		return std::move(players);
	}
}
