#ifndef __CPPJSONEXCEPTION__
#define __CPPJSONEXCEPTION__

#include <exception>
#include <string>

namespace cppjson {

class ValueNotFoundException : public std::exception {
public:
	ValueNotFoundException(std::string key) {
		err_msg = "The value corresponding to the key \"" + key + "\" does not exist";
	}
	const char* what() const noexcept {
		return err_msg.c_str();
	}

private:
	std::string err_msg;
};

}

#endif