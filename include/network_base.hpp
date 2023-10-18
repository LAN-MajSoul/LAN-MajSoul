
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
	NetworkAdpeter() = default;
	virtual ~NetworkAdpeter() = default;
};

#endif
