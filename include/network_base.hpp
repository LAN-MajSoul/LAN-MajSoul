
#ifndef _NETWORK_BASE_HPP_
#define _NETWORK_BASE_HPP_

#include <cstddef>
#include <cstdint>

struct NetworkAddr {
	char *addr;
	uint32_t port;
};

class NetworkAdpeter {
  public:
	void sendMessageTo(const char *addr, const char *data,
					   size_t size) const = delete;
	void recvMessage(char *data, size_t limit, size_t &size,
					 NetworkAddr &srcAddr) = delete;
};

#endif
