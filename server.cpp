#include "logger.hpp"
#include "network.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

auto main(int argc, const char *argv[]) -> int {
	uint32_t port;
	std::cout << "Input a Port to Bind:";
	std::cin >> port;
	NetworkServer server(port);
	logger.info("Server has been inited.");
	while (true) {
		server.waitMessage();
		server.procMessage();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}
