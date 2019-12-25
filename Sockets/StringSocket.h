#pragma once
#include "Socket.h"
#include <string.h>
#include <string>
#include <algorithm>

namespace Sockets {

	/*
	An extension class for a socket that allows to perform read and write operations on entire lines
	*/
	class StringSocket : public Socket {

	private:
		Socket* internalSocket;
		char* buffer;
		int bufferSize;
		int bufferPos;
		int bufferEnd;

	public:
		// Creates a StringSocket and stores the socket object passed as argument for functionality extension
		StringSocket(Socket* socket, int bufferSize = 1024);
		// Destroys this object and its internal socket
		~StringSocket();
		// Reads a line from this socket and returns it as a string
		virtual std::string readLine(const char* lineDelimeter = "\n");
		// Writes a line to this socket, followed by a line delimeter
		virtual void writeLine(std::string line, const char* lineDelimeter = "\n");

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
