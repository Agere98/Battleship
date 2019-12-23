#include <BattleshipServer.h>

#define BUF_SIZE 255

using namespace Sockets;

int main() {
	Socket* socket = new SocketBSD("", 2345);
	socket->listen();
	printf("Listening\n");
	while (true) {
		Socket* client = socket->accept();
		printf("Connected\n");
		char buf[BUF_SIZE];
		int l = client->read(buf, BUF_SIZE - 1);
		buf[l] = '\0';
		printf("%s\n", buf);
		client->write(buf, l);
		client->close();
	}
	socket->close();
}
