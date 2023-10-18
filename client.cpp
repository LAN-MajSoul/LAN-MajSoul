#include "logger.hpp"
#include "network.hpp"

NetworkClient client;

auto main(int argc, const char *argv[]) -> int {
	logger.info(contextInfo, "Client inited.");
	client.connect("127.0.0.1");
	return 0;
}
