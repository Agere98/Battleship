#pragma once
#include "Socket.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>

namespace Sockets {

	/*
	Socket implementation using BSD Sockets
	*/
	class SocketBSD : public Socket {

	private:
		struct sockaddr_in getAddress(const char* ipAddress, int port);

	protected:
		const int backlog = 64;
		int socket;

		SocketBSD(int socket);

	public:
		// Creates a socket
		SocketBSD();
		// Creates a socket and binds it to a specified address
		SocketBSD(const char* ipAddress, int port);

		// Associates this socket with a specified address
		virtual void bind(const char* ipAddress, int port) override;
		// Causes this socket to enter listening state
		virtual void listen() override;
		// Accepts an incoming connection attempt and returns a new socket associated with this connection
		virtual Socket* accept() override;
		// Opens a connection on this socket
		virtual void connect(const char* ipAddress, int port) override;
		// Reads bytes into buffer from this socket
		virtual int read(char* buffer, int length = 1) override;
		// Writes bytes from buffer to this socket
		virtual int write(const char* buffer, int length = 1) override;
		// Closes this socket
		virtual void close() override;
	};
}
