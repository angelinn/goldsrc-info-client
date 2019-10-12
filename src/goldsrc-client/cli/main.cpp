
#include <iostream>
#include "../client/Client.h"

int main()
{
	hlds::Client client("40.115.46.129", 27015);
	auto rules = client.QueryRules();
	for (auto& rule : rules)
		std::cout << rule.first << " = " << rule.second << std::endl;
}
