#include "network.hpp"
#include "logger.hpp"
#include "network_base.hpp"

#include <cstdint>
#include <cstring>
#include <type_traits>

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

auto DefaultUserProc(NetworkMessagePackage msgPkg) -> uint32_t {
	logger.debug("data: \"", msgPkg.data.data, "\"");
	return 0;
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
	case NetworkMessage::connectConfirm:
		logger.debug(contextInfo, "Connect Confirmed from ", msgPkg.addr.addr,
					 ":", msgPkg.addr.port);
		sessions.insert(msgPkg.addr);
		break;
	case NetworkMessage::dataGetRequest:
		logger.debug(contextInfo, "New DataGet Request from ",
					 msgPkg.addr.addr, ":", msgPkg.addr.port);
		if (sessions.count(msgPkg.addr) == 0) {
			logger.warn("Unconfirmed Request, Ingnored");
			break;
		}
		UserProc(msgPkg);
		break;
	case NetworkMessage::dataPostRequest:
		logger.debug(contextInfo, "New DataPost Request from ",
					 msgPkg.addr.addr, ":", msgPkg.addr.port);
		if (sessions.count(msgPkg.addr) == 0) {
			logger.warn("Unconfirmed Request, Ingnored");
			break;
		}
		[this, msgPkg] {
			struct NetworkMessage msg;
			memset(&msg, 0, sizeof(msg));
			msg.type = NetworkMessage::Type::dataReply;
			msg.length = 0;
			msg.verify = getVerify(msg);
			sendMessageTo(&msgPkg.addr, reinterpret_cast<const char *>(&msg),
						  sizeof(msg));
		}();
		break;
	case NetworkMessage::dataPackage:
		logger.debug(contextInfo, "New DataPackage Request from ",
					 msgPkg.addr.addr, ":", msgPkg.addr.port);
		if (sessions.count(msgPkg.addr) == 0) {
			logger.warn("Unconfirmed Request, Ingnored");
			break;
		}
		[this, msgPkg] {
			struct NetworkMessage msg;
			memset(&msg, 0, sizeof(msg));
			msg.type = NetworkMessage::Type::dataConfirm;
			msg.parameter = msgPkg.data.parameter;
			msg.length = 0;
			msg.verify = getVerify(msg);
			sendMessageTo(&msgPkg.addr, reinterpret_cast<const char *>(&msg),
						  sizeof(msg));
		}();
		UserProc(msgPkg); // 让用户处理该数据
		break;
	case NetworkMessage::dataEnd:
	case NetworkMessage::closeRequest:
	case NetworkMessage::closeReply:
	case NetworkMessage::closeConfirm:
	case NetworkMessage::closeEndup:
		break;
	default:
		logger.warn(contextInfo, "Unexcept message type (", msgPkg.data.type,
					") from ", msgPkg.addr.addr, ":", msgPkg.addr.port);
		break;
	}
	return 0;
}

void NetworkServer::procMessage() {
	while (!msgQueue.empty()) {
		serverProc(msgQueue.front());
		msgQueue.pop();
	}
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
	} while (state < 0 || getVerify(rmsg) != rmsg.verify ||
			 rmsg.type != NetworkMessage::connectReply);
	memset(&msg, 0, sizeof(msg));
	session = addr;
	msg.type = NetworkMessage::Type::connectConfirm;
	msg.length = 0;
	msg.verify = getVerify(msg);
	sendMessageTo(&addr, reinterpret_cast<const char *>(&msg), sizeof(msg));
}

void NetworkClient::send(const char *str, uint32_t size) {
	struct NetworkMessage msg;
	struct NetworkMessage rmsg;
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::dataPostRequest;
	msg.length = 0;
	msg.verify = getVerify(msg);
	struct NetworkAddr addr = session;
	int32_t state;
	do {
		logger.debug(contextInfo, "Try to Post Data to Server, Msg [",
					 msg.type, "]");
		sendMessageTo(&addr, reinterpret_cast<const char *>(&msg),
					  sizeof(msg));
		state = recvMessage(reinterpret_cast<char *>(&rmsg), sizeof(rmsg));
	} while (state < 0 || getVerify(rmsg) != rmsg.verify ||
			 rmsg.type != NetworkMessage::dataReply);
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::dataPackage;
	msg.parameter = 0; // 这个参数用于在数据包分块时标识数据包
	msg.length = size;
	memcpy(msg.data, str, size);
	msg.verify = getVerify(msg);
	do {
		logger.debug(contextInfo, "Send DataPackage to Server, Msg [",
					 msg.type, "]");
		sendMessageTo(&addr, reinterpret_cast<const char *>(&msg),
					  sizeof(msg));
		state = recvMessage(reinterpret_cast<char *>(&rmsg), sizeof(rmsg));
	} while (state < 0 || getVerify(rmsg) != rmsg.verify ||
			 rmsg.type != NetworkMessage::dataConfirm ||
			 rmsg.parameter != msg.parameter);
	memset(&msg, 0, sizeof(msg));
	msg.type = NetworkMessage::Type::dataEnd;
	msg.length = size;
	memcpy(msg.data, str, size);
	msg.verify = getVerify(msg);
	sendMessageTo(&addr, reinterpret_cast<const char *>(&msg), sizeof(msg));
}
