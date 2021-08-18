#include "CppJsonLexer.h"

namespace cppjson {
	std::string toString(const TokenType type) {
		switch (type) {
		case TokenType::LBRACE: return "Left brace";
		case TokenType::RBRACE: return "Right brace";
		case TokenType::LBRACKET: return "Left bracket";
		case TokenType::RBRACKET: return "Right bracket";
		case TokenType::COLON: return "Colon";
		case TokenType::COMMA: return "Comma";
		case TokenType::WHITESPACE: return "White space";
		case TokenType::NUMBER: return "Number";
		case TokenType::STRING: return "String";
		case TokenType::BOOLEAN: return "Boolean";
		case TokenType::T_NULL: return "Null";
		}

		throw 0xFFFFFFFF;
	}
	std::string toString(const Token& tok) {
		return "<" + toString(tok.type) + ":" + tok.value + ">";
	}

	std::vector<Token> remove_whitespace(std::vector<Token> token_list) {
		std::vector<Token> without_whitespace;

		for (const Token& tok : token_list) {
			if (tok.type != TokenType::WHITESPACE) {
				without_whitespace.push_back(tok);
			}
		}

		return without_whitespace;
	}

	std::vector<Token> tokenize(std::string json_str) {
		auto base = json_str.begin();
		auto curr = json_str.begin();

		int pre_s = 0;
		int state = 0;

		std::vector<Token> token_list;

		while (base != json_str.end()) {
			pre_s = state;
			state = (curr != json_str.end()) ? dfa::transition(state, *curr) : -1;
			if (state == -1) {
				if (dfa::isAccepted(pre_s)) {
					token_list.push_back({
						dfa::getType(pre_s),
						std::string(base, curr)
						});

					state = 0;
					base = curr;
				}
				else {
					throw 0xFFFFFFFE;
				}
			}
			else {
				curr++;
			}
		}

		return remove_whitespace(token_list);
	}

	namespace dfa {
		int transition(int state, char in) {
			if (state == 0) {
				if (in == '\"') return 1;
				if (in == '-') return 2;
				if (in == 't') return 3;
				if (in == 'f') return 4;
				if (in == '0') return 12;
				if ('1' <= in && in <= '9') return 5;
				if (in == '{') return 15;
				if (in == '}') return 16;
				if (in == '[') return 17;
				if (in == ']') return 18;
				if (in == ':') return 19;
				if (in == ',') return 20;
				if (in == ' ' || in == '\n' || in == '\t') return 21;
				if (in == 'n') return 23;

				return -1;
			}

			if (state == 1) {
				if (in == '\"') return 11;
				else return 1;
			}

			if (state == 2) {
				if ('1' <= in && in <= '9') return 5;
				else return -1;
			}

			if (state == 3) {
				if (in == 'r') return 6;
				else return -1;
			}

			if (state == 4) {
				if (in == 'a') return 7;
				else return -1;
			}

			if (state == 5) {
				if ('0' <= in && in <= '9') return 5;
				else if (in == '.') return 22;
				else return -1;
			}

			if (state == 6) {
				if (in == 'u') return 8;
				else return -1;
			}

			if (state == 7) {
				if (in == 'l') return 9;
				else return -1;
			}

			if (state == 8) {
				if (in == 'e') return 13;
				else return -1;
			}

			if (state == 9) {
				if (in == 's') return 10;
				else return -1;
			}

			if (state == 10) {
				if (in == 'e') return 14;
				else return -1;
			}

			if (state == 22) {
				if ('0' <= in && in <= '9') return 5;
				else return -1;
			}

			if (state == 23) {
				if (in == 'u') return 24;
				else return -1;
			}

			if (state == 24) {
				if (in == 'l') return 25;
				else return -1;
			}

			if (state == 25) {
				if (in == 'l') return 26;
				else return -1;
			}

			return -1;
		}

		int isAccepted(int state) {
			switch (state) {
			case 5:  // Number
			case 11: // String
			case 12: // Number(Zero)
			case 13: // Boolean(True)
			case 14: // Boolean(False)
			case 15: // {
			case 16: // }
			case 17: // [
			case 18: // ]
			case 19: // :
			case 20: // ,
			case 21: // white space
			case 26: // null
				return true;

			default:
				return false;
			}
		}

		TokenType getType(int state) {
			switch (state) {
			case  5: return TokenType::NUMBER;
			case 11: return TokenType::STRING;
			case 12: return TokenType::NUMBER;
			case 13: return TokenType::BOOLEAN;
			case 14: return TokenType::BOOLEAN;
			case 15: return TokenType::LBRACE;
			case 16: return TokenType::RBRACE;
			case 17: return TokenType::LBRACKET;
			case 18: return TokenType::RBRACKET;
			case 19: return TokenType::COLON;
			case 20: return TokenType::COMMA;
			case 21: return TokenType::WHITESPACE;
			case 26: return TokenType::T_NULL;
			}

			throw 0xFFFFFFFE;
		}
	}
}