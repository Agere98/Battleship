#include "StringSocket.h"
#include <algorithm>
#include <string.h>
#include <stdexcept>

namespace Sockets {

	int StringSocket::_read(char* buffer, int length) {
		// If there are unprocesed characters in the internal buffer
		// (after a call to readLine), read them first
		if (bufferPos != bufferEnd) {
			int size = std::min(bufferEnd - bufferPos, length);
			memcpy(buffer, this->buffer + bufferPos, size);
			bufferPos += size;
			return size;
		}
		// Else, delegate the call to the internal socket as usual
		else {
			return internalSocket->read(buffer, length);
		}
	}

	int StringSocket::_write(const char* buffer, int length) {
		return internalSocket->write(buffer, length);
	}

	StringSocket::StringSocket(Socket* socket, int bufferSize) {
		if (socket == nullptr) {
			throw std::invalid_argument("Socket is null");
		}
		internalSocket = socket;
		buffer = new char[bufferSize];
		this->bufferSize = bufferSize;
		bufferPos = bufferEnd = 0;
	}

	StringSocket::~StringSocket() {
		delete(buffer);
		delete(internalSocket);
	}

	std::string StringSocket::readLine(const char* lineDelimeter) {
		std::string line = "";
		int l = 0;
		pthread_mutex_lock(&readMutex);
		while (true) {
			// Read from the socket and append the output string
			// until the line delimeter is found
			int pos = line.find(lineDelimeter);
			if (pos == std::string::npos) {
				l = _read(buffer, bufferSize);
				if (l == 0)break;
				line.append(buffer, l);
			}
			else {
				// When the line delimeter is found, erase all characters
				// that came after it from the output string
				// and store them in the internal buffer
				// for the next read operation
				bufferEnd = l;
				int endOfLine = pos + strlen(lineDelimeter);
				int charsLeft = line.length() - endOfLine;
				bufferPos = bufferEnd - charsLeft;
				line.erase(pos);
				break;
			}
		}
		pthread_mutex_unlock(&readMutex);
		return line;
	}

	void StringSocket::writeLine(std::string line, const char* lineDelimeter) {
		const char* buffer = line.c_str();
		int charsLeft = line.length();
		pthread_mutex_lock(&writeMutex);
		while (charsLeft > 0) {
			int l = _write(buffer, charsLeft);
			if (l == 0) {
				pthread_mutex_unlock(&writeMutex);
				return;
			}
			charsLeft -= l;
		}
		_write(lineDelimeter, strlen(lineDelimeter));
		pthread_mutex_unlock(&writeMutex);
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
		pthread_mutex_lock(&readMutex);
		int result = _read(buffer, length);
		pthread_mutex_unlock(&readMutex);
		return result;
	}

	int StringSocket::write(const char* buffer, int length) {
		pthread_mutex_lock(&writeMutex);
		int result = _write(buffer, length);
		pthread_mutex_unlock(&writeMutex);
		return result;
	}

	void StringSocket::close() {
		internalSocket->close();
	}
}
