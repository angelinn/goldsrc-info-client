#pragma once

#include <memory>

namespace hlds
{
	struct QueryResponse
	{
		std::unique_ptr<char[]> response;
		size_t size;

		QueryResponse(const char* response, size_t size)
		{
			this->response = std::make_unique<char[]>(size);
			memcpy(this->response.get(), response, size);

			this->size = size;
		}
	};
}
