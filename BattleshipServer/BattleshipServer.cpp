#include <BattleshipServer.h>

using namespace Sockets;

int main() {
	Socket* server = new SocketBSD("", 2345);
	server->listen();
	std::cout << "Listening" << std::endl;
	while (true) {
		StringSocket* client = new StringSocket(server->accept());
		std::cout << "Connected" << std::endl;
		while (true) {
			std::string s = client->readLine();
			if (s.compare("") == 0)break;
			std::cout << s << std::endl;
			client->writeLine(s);
		}
		client->close();
	}
	server->close();
}
