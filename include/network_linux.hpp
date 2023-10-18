#ifndef _NETWORK_LINUX_HPP_
#define _NETWORK_LINUX_HPP_

#include "network_base.hpp"

#ifndef _WIN32

#include <sys/socket.h>

class NetworkAdpeterLinux : private NetworkAdpeter {
	NetworkAddr localAddr;
	int socketUDP;

  public:
	explicit NetworkAdpeterLinux(uint32_t port);
	void sendMessageTo(const char *addr, const char *data, size_t size) const;
	void recvMessage(char *data, size_t limit, size_t *size = nullptr,
					 NetworkAddr *srcAddr = nullptr) const;
};

#else

class NetworkAdpeterLinux : private NetworkAdpeter {
  public:
	explicit NetworkAdpeterLinux(uint32_t port) {}
};

#endif
#endif
