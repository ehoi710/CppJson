#include <iostream>
#include <string>
#include <fstream>

#include "CppJson.h"

int main(int argc, char* argv[]) {
	cppjson::Json j = cppjson::Json::loadFromFile(argv[1]);
	std::cout << j[1] << std::endl;
	
	return 0;
}
