#include <string>
#ifndef _WIN32

#include "logger.hpp"
#include "network_base.hpp"
#include "network_linux.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// #include <asm-generic/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

NetworkAdpeterLinux::NetworkAdpeterLinux(uint32_t port, uint32_t timeoutVal) {
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
	addr.sin_port = htons(this->localAddr.port = port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->localAddr.addr = "127.0.0.1";

	// set Timeout
	if (timeoutVal != 0) {
		constexpr uint32_t usecPerSec = 1000000;
		struct timeval timeVal;
		timeVal.tv_sec = timeoutVal / usecPerSec;
		timeVal.tv_usec = timeoutVal % usecPerSec;
		setsockopt(socketUDP, SOL_SOCKET, SO_RCVTIMEO,
				   reinterpret_cast<const char *>(&timeVal),
				   sizeof(struct timeval));
	}

	// Bind Port
	if (bind(socketUDP, reinterpret_cast<struct sockaddr *>(&addr), addrLen) ==
		-1) {
		logger.error(contextInfo, "Fail to Bind Socket to Port ", port);
		close(socketUDP);
		exit(-1);
	}
	logger.info(__FUNCTION__, "inited.");
}

NetworkAdpeterLinux::~NetworkAdpeterLinux() { close(socketUDP); }

void NetworkAdpeterLinux::sendMessageTo(const NetworkAddr *address,
										const char *data, size_t size) const {
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(address->port);
	addr.sin_addr.s_addr = inet_addr(address->addr.c_str());
	// logger.debug(contextInfo, "Sendto ", inet_ntoa(addr.sin_addr), ":",
	// 			 address->port);
	std::string tmp;
	for (int i = 0; i < size; ++i) {
		tmp.push_back(data[i]);
	}
	tmp.push_back('\0');
	char dat[(size * 4 + 1) / 3];
	strcpy(dat, base64Converter.base64encoder(tmp).c_str());
	sendto(socketUDP, dat, size * 4 / 3, 0,
		   reinterpret_cast<sockaddr *>(&addr), addrLen);
}
auto NetworkAdpeterLinux::recvMessage(char *data, size_t limit, size_t *size,
									  NetworkAddr *srcAddr) const -> int32_t {
	struct sockaddr_in src;
	socklen_t srcLen = sizeof(src);
	memset(&src, 0, sizeof(src));
	size_t siz;
	int timeoutCnt = 0;
	char dat[limit * 4 / 3];
	do {
		// logger.debug(contextInfo, "Waiting for UDP package...");
		siz = recvfrom(socketUDP, dat, limit * 4 / 3, 0,
					   reinterpret_cast<sockaddr *>(&src), &srcLen);
	} while (siz == -1 &&
			 (logger.warn(contextInfo, "Time Out at Recving Data!"),
			  ++timeoutCnt < 3));
	if (timeoutCnt >= 3) {
		logger.error(contextInfo, "Cannot RecvMessage (aka Timeout)!");
		return -1;
	}
	dat[siz] = '\0';
	std::string tmp = base64Converter.base64decoder(dat);
	for (int i = 0; i < tmp.size(); ++i) {
		data[i] = tmp[i];
	}
	// logger.debug(contextInfo, "Recvfrom ", inet_ntoa(src.sin_addr), " data:[
	// ", 			 data, " ]");
	if (size != nullptr) {
		*size = siz;
	}
	if (srcAddr != nullptr) {
		srcAddr->port = ntohs(src.sin_port);
		srcAddr->addr = inet_ntoa(src.sin_addr);
	}
	return 0;
}

#endif
