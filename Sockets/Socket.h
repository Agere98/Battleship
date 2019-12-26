#pragma once

namespace Sockets {

	/*
	Basic socket interface
	*/
	class Socket {

	public:
		// Associates this socket with a specified address
		virtual void bind(const char* ipAddress, int port) = 0;
		// Causes this socket to enter listening state
		virtual void listen() = 0;
		// Accepts an incoming connection attempt and returns a new socket associated with this connection
		virtual Socket* accept() = 0;
		// Opens a connection on this socket
		virtual void connect(const char* ipAddress, int port) = 0;
		// Reads bytes into buffer from this socket
		virtual int read(char* buffer, int length = 1) = 0;
		// Writes bytes from buffer to this socket
		virtual int write(const char* buffer, int length = 1) = 0;
		// Closes this socket
		virtual void close() = 0;

		virtual ~Socket() = default;
	};
}
