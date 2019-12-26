#include "ConnectionManager.h"

namespace BattleshipServer {

	void* ConnectionManager::clientBehavior(void* clientSocket) {
		pthread_detach(pthread_self());
		Sockets::StringSocket* client =
			new Sockets::StringSocket((Sockets::Socket*)clientSocket);
		while (true) {
			std::string s = client->readLine();
			if (s.compare("") == 0)break;
			std::cout << s << std::endl;
			client->writeLine(s);
		}
		client->close();
		delete(client);
		pthread_exit(NULL);
	}

	void ConnectionManager::handleConnection(Sockets::Socket* client) {
		pthread_t thread;
		pthread_create(&thread, NULL, ConnectionManager::clientBehavior, (void*)client);
	}
}
