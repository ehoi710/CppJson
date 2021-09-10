#include <iostream>
#include <string>
#include <fstream>

#include "CppJson.h"

std::string read_content(std::string file_name) {
	std::ifstream ifs(file_name);
	return std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
}

int main(int argc, char* argv[]) {
	std::string str = read_content(argv[1]);

	try {
		cppjson::Json j(str);
		std::cout << j << std::endl;
	}
	catch (cppjson::TokenizeFailedException e) {
		fprintf(stderr, "\033[1;37m%s\033[0m:%d:%d: ", argv[1], e.getLine(), e.getPos());
		fprintf(stderr, "\033[1;31merror:\033[0m Tokenize Failed\n");
	}
	catch (cppjson::ValueNotFoundException e) {
		std::cout << e.what();
	}
	
	return 0;
}
