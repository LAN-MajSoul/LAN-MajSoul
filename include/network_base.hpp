
#ifndef _NETWORK_BASE_HPP_
#define _NETWORK_BASE_HPP_

#include <cstddef>
#include <cstdint>
#include <string>

struct NetworkAddr {
	std::string addr;
	uint32_t port;

	auto operator==(const NetworkAddr &rhs) const -> bool {
		return addr == rhs.addr && port == rhs.port;
	}
	auto operator!=(const NetworkAddr &rhs) const -> bool {
		return !(*this == rhs);
	}
	auto operator<(const NetworkAddr &rhs) const -> bool {
		return addr == rhs.addr ? port < rhs.port : addr < rhs.addr;
	}
};

class NetworkAdpeter {
  public:
	NetworkAdpeter() = default;
	virtual ~NetworkAdpeter() = default;
};

class Base64Converter {
	static constexpr char sBase64[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
	char rBase64[64];

  public:
	Base64Converter();

	auto base64encoder(std::string) -> std::string;
	auto base64decoder(std::string) -> std::string;
};

extern Base64Converter base64Converter;

#endif
