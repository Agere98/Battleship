#include "SocketBSD.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>

namespace Sockets {

	SocketBSD::SocketBSD() {
		socket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (socket == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	SocketBSD::SocketBSD(const char* ipAddress, int port)
		:SocketBSD() {
		if (socket != -1) {
			bind(ipAddress, port);
		}
	}

	SocketBSD::SocketBSD(int socket) :socket(socket) {}

	sockaddr_in SocketBSD::getAddress(const char* ipAddress, int port) {
		struct sockaddr_in socketAddress;
		memset(&socketAddress, 0, sizeof(struct sockaddr_in));
		if (strcmp(ipAddress, "") == 0) {
			socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else if (inet_pton(AF_INET, ipAddress, &socketAddress.sin_addr) <= 0) {
			throw std::invalid_argument("Invalid address");
		}
		socketAddress.sin_family = AF_INET;
		socketAddress.sin_port = htons(port);
		return socketAddress;
	}

	void SocketBSD::bind(const char* ipAddress, int port) {
		struct sockaddr_in socketAddress = getAddress(ipAddress, port);
		if (::bind(socket, (struct sockaddr*) & socketAddress, sizeof(socketAddress)) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	void SocketBSD::listen() {
		if (::listen(socket, backlog) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	Socket* SocketBSD::accept() {
		int clientSocket = ::accept(socket, NULL, NULL);
		if (clientSocket == -1) {
			throw std::runtime_error(strerror(errno));
		}
		return new SocketBSD(clientSocket);
	}

	void SocketBSD::connect(const char* ipAddress, int port) {
		struct sockaddr_in socketAddress = getAddress(ipAddress, port);
		if (::connect(socket, (struct sockaddr*) & socketAddress, sizeof(socketAddress)) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	int SocketBSD::read(char* buffer, int length) {
		int size = ::read(socket, buffer, length);
		if (size == -1) {
			throw std::runtime_error(strerror(errno));
		}
		return size;
	}

	int SocketBSD::write(const char* buffer, int length) {
		int size = ::write(socket, buffer, length);
		if (size == -1) {
			throw std::runtime_error(strerror(errno));
		}
		return size;
	}

	void SocketBSD::close() {
		if (::close(socket) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}
}
