#include "logger.hpp"
#include "network.hpp"
#include <iostream>

NetworkClient client;

auto main(int argc, const char *argv[]) -> int {
	logger.info(contextInfo, "Client inited.");
	std::string str;
	std::cin >> str;
	client.connect(str.c_str());
	return 0;
}
