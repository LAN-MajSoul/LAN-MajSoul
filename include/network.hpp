#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include "network_base.hpp"
#include "network_linux.hpp"
#include "network_windows.hpp"

#include <cstdint>

// 在这里添加声明

constexpr int defaultPort = 22500;

/* Name: NetworkHoster
 * Usage:
 */
class NetworkHoster : private NetworkAdpeterLinux,
					  private NetworkAdpeterWindows {
  public:
	explicit NetworkHoster(uint32_t port = defaultPort)
		: NetworkAdpeterLinux(port), NetworkAdpeterWindows(port) {}
};

#endif
