#include "CppJsonBase.h"

namespace cppjson{
JsonString::JsonString() : str() { }
JsonString::JsonString(std::string str) : str(str) { }

std::string JsonString::toString() const {
	return '\"' + str + '\"';
}

/**********/

JsonNumber::JsonNumber() : num() { }
JsonNumber::JsonNumber(double num) : num(num) { }
JsonNumber::JsonNumber(std::string num) {
	this->num = std::stod(num);
}

double JsonNumber::toNumber() const {
	return num;
}
std::string JsonNumber::toString() const {
	std::string str = std::to_string(num);
	while (str.back() == '0') str.pop_back();
	return str;
}

/**********/

JsonBoolean::JsonBoolean() : boolean() { }
JsonBoolean::JsonBoolean(std::string boolean) : boolean() {
	if(boolean == "true") this->boolean = true;
	if(boolean == "false") this->boolean = false;
}

bool JsonBoolean::toBoolean() const {
	return boolean;
}
std::string JsonBoolean::toString() const {
	return boolean ? "true" : "false";
}

JsonObject::JsonObject() : map() { }
JsonObject::JsonObject(std::vector<Entry> map) : map() {
	for (const auto& entry : map) {
		this->map[entry.first->toString()] = entry.second;
	}
}

JsonObject::~JsonObject() {
	for (auto entry : map) {
		delete entry.second;
	}
}

JsonBase* JsonObject::find(std::string key) const {
	auto it = map.find(key);
	if(it == map.end()) {
		throw ValueNotFoundException(key);
	}
	else {
		return it->second;
	}
}

std::string JsonObject::toString() const {
	std::string str = "{";
	for (auto iter = map.begin(); iter != map.end(); iter++) {
		if (iter != map.begin()) {
			str += ", ";
		}

		str += iter->first + ": " + iter->second->toString();
	}
	str += "}";

	return str;
}

/**********/

JsonArray::JsonArray() : array() { }
JsonArray::JsonArray(std::vector<JsonBase*> array) : array(array) { }
JsonArray::~JsonArray() {
	for(auto entry : array) {
		delete entry;
	}
}

JsonBase* JsonArray::get(size_t idx) const {
	if (idx >= array.size()) {
		throw ArrayOutOfBoundException(idx, array.size());
	}
	else {
		return array[idx];
	}
}
std::string JsonArray::toString() const {
	std::string str = "[";
	for (int i = 0; i < array.size(); i++) {
		if (i != 0) {
			str += ", ";
		}

		str += array[i]->toString();
	}
	str += "]";

	return str;
}

/**********/

JsonNull ::JsonNull() { }
std::string JsonNull::toString() const {
	return "null";
}

}
