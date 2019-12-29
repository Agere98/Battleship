#include <ConnectionManager.h>
#include <SocketBSD.h>
#include <iostream>
#include <pthread.h>

#define SERVER_PORT 2680

using namespace std;
using namespace Sockets;
using namespace BattleshipServer;

void* runServer(void* serverSocket) {
	Socket* server = (Socket*)serverSocket;
	ConnectionManager connectionManager;
	while (true) {
		try {
			connectionManager.handleConnection(server->accept());
		}
		catch (std::runtime_error & exception) {
			cout << exception.what() << endl;
		}
	}
}

int main() {
	SocketBSD server("", SERVER_PORT);
	server.listen();
	pthread_t serverThread;
	pthread_create(&serverThread, NULL, runServer, (void*)&server);
	cout << "The server is running on port " << SERVER_PORT << ", type 'stop' to stop the server" << endl;
	string s;
	while (getline(cin, s)) {
		if (s == "stop") {
			break;
		}
	}
	server.close();
	cout << "The server has been stopped correctly" << endl;
}
