#ifndef __CPPJSONLEXER__
#define __CPPJSONLEXER__

#include <vector>
#include <string>
#include <regex>
#include <sstream>

#include "CppJsonException.h"
#include "dfa.h"

namespace cppjson {
	enum class TokenType {
		LBRACE, RBRACE,
		LBRACKET, RBRACKET,
		COLON, COMMA, WHITESPACE,
		NUMBER, STRING, BOOLEAN, T_NULL
	};

	struct Token {
		TokenType type;
		std::string value;
		int line, pos;
	};

	namespace dfa {
		int transition(int state, char in);
		int isAccepted(int state);

		TokenType getType(int state);
	}

	std::string toString(const TokenType type);
	std::string toString(const Token& tok);
	
	std::vector<std::string> split(std::string str);

	std::vector<Token> remove_whitespace(std::vector<Token> token_list);
	std::vector<Token> tokenize(std::vector<std::string> str_list);
}

#endif
