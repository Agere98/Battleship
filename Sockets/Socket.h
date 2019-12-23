#pragma once

namespace Sockets {

	class Socket {

	public:
		virtual void bind(const char* ipAddress, int port) = 0;
		virtual void listen() = 0;
		virtual Socket* accept() = 0;
		virtual void connect(const char* ipAddress, int port) = 0;
		virtual int read(char* buffer, int length = 1) = 0;
		virtual void write(char* buffer, int length = 1) = 0;
		virtual void close() = 0;
	};
}
