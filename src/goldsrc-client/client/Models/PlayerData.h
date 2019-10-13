#pragma once

#include "../Common.h"

#include <cstring>

namespace hlds
{
	struct PlayerData
	{
		int index;
		std::string name;
		long score;
		float duration;
	};
}
