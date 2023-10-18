#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include "network_base.hpp"
#include "network_linux.hpp"
#include "network_windows.hpp"

#include <cstdint>
#include <queue>
#include <vector>

// 在这里添加声明

constexpr int defaultPort = 22500;

struct NetworkMessage {
	enum Type : uint32_t {
		// 三次握手
		connectRequest, // 客户端请求连接
		connectReply,	// 服务器回应连接
		connectConfirm, // 客户端确认连接
		// 数据流式传输
		dataGetRequest,	 // 客户端请求数据
		dataPostRequest, // 客户端发送数据
		dataReply,		 // 服务器答复请求
		dataPackage,	 // 数据包裹
		dataConfirm,	 // 数据成功接收
		dataEnd,		 // 数据发送完毕
		// 四次挥手
		closeRequest, // 客户端请求下线
		closeReply,	  // 服务器回应下线
		closeConfirm, // 客户端确认下线
		closeEndup,	  // 服务器删除记录
	} type;
	uint32_t length;	// 数据长度
	uint16_t parameter; // 额外参数
	uint8_t verify;		// 校验码 数据的8位异或和
	uint8_t zero[5];	// 填充字节 置0
	char data[1024];	// 数据
};

struct NetworkMessagePackage {
	NetworkMessage data;
	size_t size;
	NetworkAddr addr;
};

/* Name: NetworkHoster
 * Usage:
 */
class NetworkHoster : public NetworkAdpeterLinux,
					  public NetworkAdpeterWindows {
  public:
	explicit NetworkHoster(uint32_t port)
		: NetworkAdpeterLinux(port), NetworkAdpeterWindows(port) {}
	~NetworkHoster() override = default;
	static auto getVerify(const NetworkMessage &msg) -> uint8_t;
};

// 由用户定义的事件处理函数
auto UserProc(NetworkMessagePackage msgPkg) -> uint32_t;

/* Name: NetworkServer
 * Usage:
 */
class NetworkServer : public NetworkHoster {
	std::vector<NetworkAddr> sessions;
	std::queue<NetworkMessagePackage> msgQueue;

	auto serverProc(NetworkMessagePackage msgPkg) -> uint32_t;

  public:
	explicit NetworkServer(uint32_t port = defaultPort)
		: NetworkHoster(port) {}

	void waitMessage();
	void procMessage();
};

/* Name: NetworkClient
 * Usage:
 */
class NetworkClient : public NetworkHoster {
  public:
	explicit NetworkClient(uint32_t port = defaultPort)
		: NetworkHoster(port) {}

	void connect(const char *server);
	void send(const char *str);
};

#endif
