#pragma once

#ifdef COMPILING_DLL 
/*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <vector>
#include <string>

namespace hlds
{
	typedef std::vector<std::pair<std::string, std::string>> RulesVector;
	const int PACKET_SIZE = 1400;
}
