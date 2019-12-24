#include "StringSocket.h"

namespace Sockets {

	StringSocket::StringSocket(Socket* socket, int bufferSize) {
		internalSocket = socket;
		buffer = new char[bufferSize];
		this->bufferSize = bufferSize;
		bufferPos = bufferEnd = 0;
	}

	StringSocket::~StringSocket() {
		delete(buffer);
	}

	std::string StringSocket::readLine(const char* lineDelimeter) {
		std::string line = "";
		int l = 0;
		while (true) {
			int pos = line.find(lineDelimeter);
			if (pos == std::string::npos) {
				l = read(buffer, bufferSize);
				if (l == 0)break;
				line.append(buffer, l);
			}
			else {
				bufferEnd = l;
				int endOfLine = pos + strlen(lineDelimeter);
				int charsLeft = line.length() - endOfLine;
				bufferPos = bufferEnd - charsLeft;
				line.erase(pos);
				break;
			}
		}
		return line;
	}

	void StringSocket::writeLine(std::string line, const char* lineDelimeter) {
		const char* buffer = line.c_str();
		int charsLeft = line.length();
		while (charsLeft > 0) {
			int l = write(buffer, charsLeft);
			if (l <= 0) {
				return;
			}
			charsLeft -= l;
		}
		write(lineDelimeter, strlen(lineDelimeter));
	}

	void StringSocket::bind(const char* ipAddress, int port) {
		internalSocket->bind(ipAddress, port);
	}

	void StringSocket::listen() {
		internalSocket->listen();
	}

	Socket* StringSocket::accept() {
		return internalSocket->accept();
	}

	void StringSocket::connect(const char* ipAddress, int port) {
		internalSocket->connect(ipAddress, port);
	}

	int StringSocket::read(char* buffer, int length) {
		if (bufferPos == bufferEnd) {
			return internalSocket->read(buffer, length);
		}
		else {
			int size = std::min(bufferEnd - bufferPos, length);
			memcpy(buffer, this->buffer + bufferPos, size);
			bufferPos += size;
			return size;
		}
	}

	int StringSocket::write(const char* buffer, int length) {
		return internalSocket->write(buffer, length);
	}

	void StringSocket::close() {
		internalSocket->close();
	}
}
