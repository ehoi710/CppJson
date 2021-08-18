#include <iostream>
#include <string>

#include "CppJson.h"

const char* json_str = "{ \"name\": \"John\", \"surname\": \"Doe\", \"phone\": null }";

int main() {
	cppjson::Json j(json_str);
	std::cout << j << std::endl;
	try {
		std::cout << j["membre"];
	}
	catch (cppjson::ValueNotFoundException e) {
		std::cout << e.what();
	}
	
	return 0;
}