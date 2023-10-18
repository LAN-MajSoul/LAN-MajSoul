#include "network.hpp"
#include "network_base.hpp"

#include <cstdint>
#include <cstring>

// 在这里给出头文件中声明对应的定义

auto NetworkHoster::getVerify(const NetworkMessage &msg) -> uint8_t {
	uint8_t *dat = reinterpret_cast<uint8_t *>(const_cast<char *>(msg.data));
	uint8_t res = static_cast<uint8_t>(msg.type >> 24) ^
				  static_cast<uint8_t>(msg.type >> 16) ^
				  static_cast<uint8_t>(msg.type >> 8) ^
				  static_cast<uint8_t>(msg.type) ^
				  static_cast<uint8_t>(msg.length >> 8) ^
				  static_cast<uint8_t>(msg.length);
	while (dat != reinterpret_cast<uint8_t *>(
					  const_cast<char *>(msg.data + msg.length))) {
		res ^= *dat, ++dat;
	}
	return res;
}

void NetworkServer::waitMessage() {
	struct NetworkMessagePackage msgPkg;
	do {
		recvMessage(reinterpret_cast<char *>(&msgPkg.data),
					sizeof(msgPkg.data), &msgPkg.size, &msgPkg.addr);
	} while (getVerify(msgPkg.data) != msgPkg.data.verify);
	msgQueue.emplace(msgPkg);
}

void NetworkClient::connect(const char *server) {
	struct NetworkMessage msg;
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::connectRequest;
	msg.length = 0;
	msg.verify = getVerify(msg);
	do {
		sendMessageTo(server, reinterpret_cast<const char *>(&msg),
					  sizeof(msg));
		recvMessage(reinterpret_cast<char *>(&msg), sizeof(msg));
	} while (getVerify(msg) != msg.verify);
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::connectConfirm;
	msg.length = 0;
	msg.verify = getVerify(msg);
	sendMessageTo(server, reinterpret_cast<const char *>(&msg), sizeof(msg));
}

void NetworkClient::send(const char *str) {}