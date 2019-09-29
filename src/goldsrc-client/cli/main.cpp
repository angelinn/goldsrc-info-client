
#include <iostream>
#include "../client/Client.h"

int main()
{
	hlds::Client client;
	client.QueryRules("40.115.46.129", 27015);
}
