#include "network.hpp"

NetworkClient client;

auto main(int argc, const char *argv[]) -> int {
	client.connect("127.0.0.1");
	return 0;
}
