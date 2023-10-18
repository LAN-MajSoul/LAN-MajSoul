#include "network.hpp"

#include <chrono>
#include <thread>

NetworkServer server;

auto main(int argc, const char *argv[]) -> int {
	while (true) {
		server.waitMessage();
		server.procMessage();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}
