#include "network.hpp"
#include "logger.hpp"
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

auto NetworkServer::serverProc(NetworkMessagePackage msgPkg) -> uint32_t {
	switch (msgPkg.data.type) {
	case NetworkMessage::nulltype:
	case NetworkMessage::connectRequest:
		logger.debug(contextInfo, "New Connect Request from ",
					 msgPkg.addr.addr, ":", msgPkg.addr.port);
		[this, msgPkg] {
			struct NetworkMessage msg;
			memset(&msg, 0, sizeof(msg));
			msg.type = NetworkMessage::Type::connectReply;
			msg.length = 0;
			msg.verify = getVerify(msg);
			sendMessageTo(&msgPkg.addr, reinterpret_cast<const char *>(&msg),
						  sizeof(msg));
		}();
		break;
	case NetworkMessage::connectReply:
	case NetworkMessage::connectConfirm:
	case NetworkMessage::dataGetRequest:
	case NetworkMessage::dataPostRequest:
	case NetworkMessage::dataReply:
	case NetworkMessage::dataPackage:
	case NetworkMessage::dataConfirm:
	case NetworkMessage::dataEnd:
	case NetworkMessage::closeRequest:
	case NetworkMessage::closeReply:
	case NetworkMessage::closeConfirm:
	case NetworkMessage::closeEndup:
		break;
	}
	return 0;
}

void NetworkServer::procMessage() {
	if (msgQueue.empty()) {
		return;
	}
	serverProc(msgQueue.front());
	msgQueue.pop();
}

void NetworkServer::waitMessage() {
	struct NetworkMessagePackage msgPkg;
	int32_t state;
	do {
		state = recvMessage(reinterpret_cast<char *>(&msgPkg.data),
							sizeof(msgPkg.data), &msgPkg.size, &msgPkg.addr);
	} while (state < 0 || getVerify(msgPkg.data) != msgPkg.data.verify);
	msgQueue.emplace(msgPkg);
	logger.debug(contextInfo, "msgPkg [", msgPkg.data.type, ",",
				 msgPkg.addr.addr, ",", msgPkg.addr.port,
				 "] has been emplaced MsgQueue.");
}

void NetworkClient::connect(const char *server, uint32_t port) {
	struct NetworkMessage msg;
	struct NetworkMessage rmsg;
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::connectRequest;
	msg.length = 0;
	msg.verify = getVerify(msg);
	struct NetworkAddr addr;
	addr.addr = server;
	addr.port = port;
	int32_t state;
	do {
		logger.debug(contextInfo, "Try to connect server at ", server, ":",
					 port, " Msg [", msg.type, "]");
		sendMessageTo(&addr, reinterpret_cast<const char *>(&msg),
					  sizeof(msg));
		state = recvMessage(reinterpret_cast<char *>(&rmsg), sizeof(rmsg));
	} while (state < 0 || getVerify(rmsg) != rmsg.verify);
	memset(&rmsg, 0, sizeof(rmsg));
	rmsg.type = NetworkMessage::Type::connectConfirm;
	rmsg.length = 0;
	rmsg.verify = getVerify(rmsg);
	sendMessageTo(&addr, reinterpret_cast<const char *>(&rmsg), sizeof(msg));
}

void NetworkClient::send(const char *str) {}