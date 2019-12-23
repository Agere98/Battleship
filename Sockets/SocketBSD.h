#pragma once
#include "Socket.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

namespace Sockets {

	class SocketBSD : public Socket {

	private:
		struct sockaddr_in getAddress(const char* ipAddress, int port);

	protected:
		const int backlog = 64;
		int socket;

		SocketBSD(int socket);

	public:
		SocketBSD();
		SocketBSD(const char* ipAddress, int port);

		virtual void bind(const char* ipAddress, int port) override;
		virtual void listen() override;
		virtual Socket* accept() override;
		virtual void connect(const char* ipAddress, int port) override;
		virtual int read(char* buffer, int length = 1) override;
		virtual void write(char* buffer, int length = 1) override;
		virtual void close() override;
	};
}
