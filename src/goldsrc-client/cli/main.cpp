
#include <iostream>
#include "../client/Client.h"

int main()
{
	hlds::Client client;
	auto rules = client.QueryRules("40.115.46.129", 27015);
	for (auto& rule : rules)
		std::cout << rule.first << " = " << rule.second << std::endl;
}
