#include "ConnectionManager.h"
#include <Player.h>
#include <PlayerCommands.h>
#include <StringSocket.h>
#include <pthread.h>
#include <string>
#include <stdexcept>

namespace BattleshipServer {

	void* ConnectionManager::clientBehavior(void* clientSocket) {
		pthread_detach(pthread_self());
		Sockets::StringSocket client((Sockets::Socket*)clientSocket);
		Player player(client, PlayerCommands::instance());
		while (true) {
			std::string command = client.readLine();
			if (command.compare("exit") == 0 || command.compare("") == 0) {
				player.parseCommand("leave");
				break;
			}
			player.parseCommand(command);
		}
		client.close();
		pthread_exit(NULL);
	}

	void ConnectionManager::handleConnection(Sockets::Socket* client) {
		if (client == nullptr) {
			throw std::invalid_argument("Client is null");
		}
		pthread_t thread;
		pthread_create(&thread, NULL, ConnectionManager::clientBehavior, (void*)client);
	}
}
