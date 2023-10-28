#include "logger.hpp"
#include "network.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>

auto main(int argc, const char *argv[]) -> int {
	uint32_t port;
	std::cout << "Input a Port to Bind:";
	std::cin >> port;
	NetworkClient client(port);
	logger.info("Client has been inited.");
	std::string str;
	std::cout << "Input Server Address (eg. xxx.xxx.xxx.xxx:xxxxx):\n";
	std::cin >> str,
		str.find(':') != std::string::npos
			? (port = atoi(str.substr(str.find(':') + 1, str.size()).c_str()),
			   str = str.substr(0, str.find(':')), 0)
			: (std::cin >> port, 0);
	client.connect(str.c_str(), port);
	while (true) {
		std::cin >> str;
		client.send(str.c_str(), str.size());
	}
	return 0;
}
