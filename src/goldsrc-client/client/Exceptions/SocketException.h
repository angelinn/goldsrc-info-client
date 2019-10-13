#pragma once

#include <stdexcept>

namespace hlds
{
	class SocketException : public std::runtime_error
	{
	public:
		SocketException(const char* message) : std::runtime_error(message)
		{  }
	};
}
