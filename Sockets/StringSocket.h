#pragma once
#include "Socket.h"
#include <string.h>
#include <string>
#include <algorithm>

namespace Sockets {

	class StringSocket : public Socket {

	private:
		Socket* internalSocket;
		char* buffer;
		int bufferSize;
		int bufferPos;
		int bufferEnd;

	public:
		StringSocket(Socket* socket, int bufferSize = 1024);
		~StringSocket();
		virtual std::string readLine(const char* lineDelimeter = "\n");
		virtual void writeLine(std::string line, const char* lineDelimeter = "\n");
		virtual void bind(const char* ipAddress, int port) override;
		virtual void listen() override;
		virtual Socket* accept() override;
		virtual void connect(const char* ipAddress, int port) override;
		virtual int read(char* buffer, int length = 1) override;
		virtual int write(const char* buffer, int length = 1) override;
		virtual void close() override;
	};
}
