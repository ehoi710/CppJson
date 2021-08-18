#ifndef __CPPJSONLEXER__
#define __CPPJSONLEXER__

#include <vector>
#include <string>
#include <regex>

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
	};

	namespace dfa {
		int transition(int state, char in);
		int isAccepted(int state);

		TokenType getType(int state);
	}

	std::string toString(const TokenType type);
	std::string toString(const Token& tok);

	std::vector<Token> remove_whitespace(std::vector<Token> token_list);
	std::vector<Token> tokenize(std::string json_str);
}

#endif