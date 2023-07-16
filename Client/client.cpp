#include <iostream>
#include <string>
#include "../NetWork/message.h"
#include "../NetWork/net_client.h"
#include "../NetWork/net_connection.h"
#include "../NetWork/net_deque.h"
#include "../NetWork/net_server.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomClient : public net_client<CustomMsgTypes> {
public:
	void PingServer()	{
		message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerPing;
		std::string str = "Hello\n";

		msg << str;
		Send(msg);
	}

	void MessageAll()
	{
		message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;		
		Send(msg);
	}
};

int main() {
	std::cout << "YES" << std::endl;
	CustomClient c;
	c.Connect("127.0.0.1", 60002);
	c.PingServer();
	c.PingServer();
	c.PingServer();
	return 0;
}