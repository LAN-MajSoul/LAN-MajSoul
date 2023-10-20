#include "network_base.hpp"
#include "logger.hpp"

#include <cstdint>
#include <string>

Base64Converter::Base64Converter() {
	for (char i = 0; i < 64; ++i) {
		rBase64[sBase64[i]] = i;
	}
}

auto Base64Converter::base64encoder(std::string str) -> std::string {
	// logger.debug(contextInfo, "encoding string ", str, "...");
	std::string res;
	for (int i = 0; i < (str.size() / 3 * 3); i += 3) {
		uint32_t bits = (str[i] & 0xff) << 16 | (str[i + 1] & 0xff) << 8 |
						(str[i + 2] & 0xff);
		res += sBase64[(bits >> 18) & 0x3f];
		res += sBase64[(bits >> 12) & 0x3f];
		res += sBase64[(bits >> 6) & 0x3f];
		res += sBase64[bits & 0x3f];
	}
	if (str.size() % 3 == 1) {
		int bits = (str[str.size() - 1] & 0xff) << 4;
		res += sBase64[(bits >> 6) & 0x3f];
		res += sBase64[bits & 0x3f];
		res += '=';
		res += '=';
	}
	else if (str.size() % 3 == 2) {
		int bits = (str[str.size() - 2] & 0xff) << 10 |
				   (str[str.size() - 1] & 0xff) << 2;
		res += sBase64[(bits >> 12) & 0x3f];
		res += sBase64[(bits >> 6) & 0x3f];
		res += sBase64[bits & 0x3f];
		res += '=';
	}
	// logger.debug(contextInfo, "encode result ", res, ".");
	return res;
}

auto Base64Converter::base64decoder(std::string str) -> std::string {
	// logger.debug(contextInfo, "decoding string ", str, "...");
	std::string res;
	while (str.back() == '\0') {
		str.pop_back();
	}
	for (int i = 0; i < str.size(); i += 4) {
		int bits =
			((rBase64[str[i]] & 0x3f) << 18) |
			((rBase64[str[i + 1]] & 0x3f) << 12) |
			(str[i + 2] == '=' ? 0 : ((rBase64[str[i + 2]] & 0x3f) << 6)) |
			(str[i + 3] == '=' ? 0 : (rBase64[str[i + 3]] & 0x3f));
		res += static_cast<char>((bits >> 16) & 0xff);
		res += static_cast<char>((bits >> 8) & 0xff);
		res += static_cast<char>(bits & 0xff);
	}
	// logger.debug(contextInfo, "decode result ", res, ".");
	return res;
}

Base64Converter base64Converter;