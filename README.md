# GoldSource Info Client

**goldsrc-info-client** is a C++ client for querying the Valve's GoldSource engine games.

Created and tested for **Counter-Strike 1.6** running on **HLDS**.

The project consist of a dynamic-linked library where the implementation of the client lies and a test console application.
The library is **Windows** only and uses the **winsock2** APIs for the UDP connection to the server.

## About

Using this library you can create an application that shows information about your Counter-Strike 1.6 or other goldsrc game server.
You can request the following information:
* **Generic server information** - returns server name, current map, min/max players and more - for more detailed information check the [InfoResponse](src/goldsrc-client/client/Models/InfoResponse.h) class.
* **Server rules** - returns all the cvars that the server exposes
* **Players** - returns all players with id, frag count and duration
* **Ping** - calculates the latency to the server

Implementation based on https://developer.valvesoftware.com/wiki/Server_queries

## Usage

### Create a client object:
```cpp
hlds::Client client(serverIP, serverPort);
```

### Use the client to query the server:

* Query server info
```cpp
hlds::InfoResponse info = client.QueryInfo();
std::cout << info.name << ", " << info.game << ", " << info.map
          << ", " << info.players << " / " << info.maxPlayers << std::endl;
```

* Query rules
```cpp
RulesVector rules = client.QueryRules();
for (auto& rule : rules)
{
  std::cout << rule.first << " = " << rule.second << std::endl;
}
```

* Query players
```cpp
std::vector<hlds::PlayerData> players = client.QueryPlayers();
std::cout << "Players count: " << players.size() << std::endl;

for (auto& player : players)
{
  std::cout << "[" << player.index << "] " << player.name
            << ", " << player.score << " frags, " << player.duration << std::endl;	
}
```

* Calculate ping - return the latency to the server in ms. Uses `std::chrono::high_resolution_clock` to calculate the latency.
```cpp
size_t latency = client.QueryPing();
std::cout << "Latency: " << latency << std::endl;
```

## Troubleshooting
If the server is not available or there's a problem parsing the packets, an exception will be thrown.

## License
This software is licensed under the terms of the MIT license.

