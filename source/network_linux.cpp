#ifndef _WIN32

#include "logger.hpp"
#include "network_linux.hpp"

#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <asm-generic/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

NetworkAdpeterLinux::NetworkAdpeterLinux(uint32_t port) {
	// Create Socket
	socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketUDP == -1) {
		logger.error(contextInfo, "Cannot Create Socket!");
		exit(-1);
	}

	// Name Addr
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET; // use ipv4
	addr.sin_port = htonl(this->localAddr.port = port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->localAddr.addr = new char[10]{"127.0.0.1"};

	// set Timeout
	constexpr uint32_t timeoutVal = 200000; // 200ms
	constexpr uint32_t usecPerSec = 1000000;
	struct timeval timeVal;
	timeVal.tv_sec = timeoutVal / usecPerSec;
	timeVal.tv_usec = timeoutVal % usecPerSec;
	setsockopt(socketUDP, SOL_SOCKET, SO_RCVTIMEO,
			   reinterpret_cast<const char *>(&timeVal),
			   sizeof(struct timeval));

	// Bind Port
	if (bind(socketUDP, reinterpret_cast<struct sockaddr *>(&addr), addrLen) ==
		-1) {
		logger.error(contextInfo, "Fail to Bind Socket to Port ", port);
		close(socketUDP);
		exit(-1);
	}
}
void NetworkAdpeterLinux::sendMessageTo(const char *address, const char *data,
										size_t size) const {
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htonl(this->localAddr.port);
	addr.sin_addr.s_addr = inet_addr(address);
	sendto(socketUDP, data, size, 0, reinterpret_cast<sockaddr *>(&addr),
		   addrLen);
}
void NetworkAdpeterLinux::recvMessage(char *data, size_t limit, size_t &size,
									  NetworkAddr &srcAddr) const {
	struct sockaddr_in src;
	socklen_t srcLen = sizeof(src);
	memset(&src, 0, sizeof(src));
	size = recvfrom(socketUDP, data, limit, 0,
					reinterpret_cast<sockaddr *>(&src), &srcLen);
	srcAddr.port = this->localAddr.port;
	srcAddr.addr = inet_ntoa(src.sin_addr);
}

#endif
