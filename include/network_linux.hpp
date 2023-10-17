#ifndef _NETWORK_LINUX_HPP_
#define _NETWORK_LINUX_HPP_

#include "network_base.hpp"

#ifndef _WIN32_

#include <sys/socket.h>

class NetworkAdpeterLinux : private NetworkAdpeter {
	NetworkAddr localAddr;
	int socketUDP;

  public:
	explicit NetworkAdpeterLinux(uint32_t port);
	void sendMessageTo(const char *addr, const char *data, size_t size) const;
	void recvMessage(char *data, size_t limit, size_t &size,
					 NetworkAddr &srcAddr) const;
};

#else

class NetworkAdpeterLinux : NetworkAdpeter {
	explicit NetworkAdpeterLinux(uint32_t port) {}
};

#endif
#endif
