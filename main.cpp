#include <iostream>

#include "CppJson.h"
#include "CppJsonParser.h"

const char* json_str = "{ \"member\": [\"a\", 123, true] }";

int main() {
	std::vector<cppjson::Token> token_list = cppjson::tokenize(json_str);
	
	for(const cppjson::Token& tok : token_list) {
		std::cout << toString(tok) << std::endl;
	}
	
	return 0;
}