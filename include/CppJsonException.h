#ifndef __CPPJSONEXCEPTION__
#define __CPPJSONEXCEPTION__

#include <exception>
#include <sstream>
#include <string>

#include <stdio.h>

namespace cppjson {

class CppJsonException : public std::exception {
public:
	CppJsonException() {
		this->message = "";
	}
	CppJsonException(std::string message) {
		this->message = message;
	}
	
	virtual const char* what() const noexcept {
		return message.c_str();
	}
	
protected:
	std::string message;
};

class ValueNotFoundException : public CppJsonException {
public:
	ValueNotFoundException(std::string key) {
		message = "The value corresponding to the key \"" + key + "\" does not exist";
	}
};

class TokenizeFailedException : public CppJsonException {
public:
	TokenizeFailedException(int line, int pos) : line(line), pos(pos) {	}
	
	int getLine() { return line; }
	int getPos()  { return pos;  }
	
private:
	int line, pos;
};

class ParsingFailedException : public CppJsonException {
public:
	ParsingFailedException(int line, int pos, std::string message) : 
		line(line), pos(pos), CppJsonException(message) { }
	
	int getLine() { return line; }
	int getPos()  { return pos; }

private:
	int line, pos;
};

class ArrayOutOfBoundException : public CppJsonException {
public:
	ArrayOutOfBoundException(int idx, int size) {
		this->idx = idx;
		this->size = size;
		
		std::stringstream ss;
		ss << "Index " << idx << " is out of array bound " << size << "\n";
		message = ss.str();
	}
	
private:
	int idx;
	int size;
};

class NotImplementedException : public CppJsonException {
public:
	NotImplementedException() {}

	const char* what() {
		return "Not Implemented";
	}

private:

};

}

#endif
