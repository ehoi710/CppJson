#include "CppJson.h"

namespace cppjson {
	Json::Json(std::string json_str) {
		this->json = parse(tokenize(json_str));
	}
	Json::Json(std::shared_ptr<JsonBase> json) {
		this->json = json;
	}

	Json::operator std::string() {
		return std::dynamic_pointer_cast<JsonString>(json)->toString();
	}
	Json::operator double() {
		return std::dynamic_pointer_cast<JsonNumber>(json)->toNumber();
	}
	Json::operator bool() {
		return std::dynamic_pointer_cast<JsonBoolean>(json)->toBoolean();
	}

	Json Json::operator[](const char* key) {
		return this->operator[](std::string(key));
	}
	Json Json::operator[](std::string key) {
		return std::dynamic_pointer_cast<JsonObject>(json)->find(key);
	}

	Json Json::operator[](int idx) {
		return std::dynamic_pointer_cast<JsonArray>(json)->get(idx);
	}

	Json& Json::operator=(std::shared_ptr<JsonBase> json) {
		this->json = json;
		return *this;
	}
	
	std::string Json::toString() const {
		return this->json->toString();
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
