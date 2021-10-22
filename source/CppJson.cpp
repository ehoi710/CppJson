#include "CppJson.h"

std::string read_content(std::string file_name) {
	std::ifstream ifs(file_name);
	return std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
}

namespace cppjson {
	Json::Json() {
		this->json = nullptr;
	}
	Json::Json(std::shared_ptr<JsonBase> json) {
		this->json = json;
	}

	Json::operator std::string() {
		return json->toString();
	}
	Json::operator double() {
		return json->toNumber();
	}
	Json::operator bool() {
		return json->toBoolean();
	}

	Json Json::operator[](const char* key) {
		return this->operator[](std::string(key));
	}
	Json Json::operator[](std::string key) {
		return json->find(key);
	}

	Json Json::operator[](int idx) {
		return json->get(idx);
	}

	Json& Json::operator=(std::shared_ptr<JsonBase> json) {
		this->json = json;
		return *this;
	}
	
	std::string Json::toString() const {
		return json->toString();
	}
	
	Json Json::loadFromFile(std::string file_name) {
		std::string file_content = read_content(file_name);
		std::vector<std::string> split_str = split(file_content);
		
		Json json;
		
		try {
			json = parse(tokenize(split_str));
		}
		catch (cppjson::TokenizeFailedException e) {
			fprintf(stderr, "\033[1;37m%s\033[0m:%d:%d: ", file_name.c_str(), e.getLine(), e.getPos());
			fprintf(stderr, "\033[1;31merror:\033[0m Tokenize Failed\n");
		}
		catch (cppjson::ParsingFailedException e) {
			fprintf(stderr, "\033[1;37m%s\033[0m:%d:%d: ", file_name.c_str(), e.getLine(), e.getPos());
			fprintf(stderr, "\033[1;31merror:\033[0m %s\n", e.what());
		}
		catch (cppjson::ValueNotFoundException e) {
			fprintf(stderr, "%s\n", e.what());
		}
		catch (cppjson::ArrayOutOfBoundException e) {
			fprintf(stderr, "%s\n", e.what());
		}
		catch (unsigned int e) {
			printf("%X\n", e);
		}
		
		return json;
	}
}

std::ostream& operator<<(std::ostream& os, const cppjson::JsonBase& json) {
	os << json.toString();
	return os;
}
std::ostream& operator<<(std::ostream& os, const cppjson::Json& json) {
	os << json.toString();
	return os;
}
