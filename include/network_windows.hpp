#ifndef _NETWORK_WINDOWS_HPP_
#define _NETWORK_WINDOWS_HPP_

#include "network_base.hpp"

#ifdef _WIN32_

#include <windows.h>

class NetworkAdpeterWindows : private NetworkAdpeter {
  public:
	  explicit NetworkAdpeterWindows(uint32_t port);
	  void sendMessageTo(const char *addr, const char *data, int limit);
	  void recvMessage(char *data, int &size, NetworkAddr &srcAddr);
};

#else

class NetworkAdpeterWindows : private NetworkAdpeter {
  public:
	  explicit NetworkAdpeterWindows(uint32_t port) {}
};

#endif
#endif
