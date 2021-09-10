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

	std::vector<Token> remove_whitespace(std::vector<Token> token_list) {
		std::vector<Token> without_whitespace;

		for (const Token& tok : token_list) {
			if (tok.type != TokenType::WHITESPACE) {
				without_whitespace.push_back(tok);
			}
		}

		return without_whitespace;
	}
	
	std::vector<std::string> split(std::string str) {
		std::vector<std::string> list;
		std::stringstream ss(str);
		std::string line;
		
		while(std::getline(ss, line, '\n')) {
			if(line.back() == '\r') line.pop_back();
			list.push_back(line);
		}
		
		return list;
	}
	
	std::vector<Token> tokenize(std::string json_str) {
		std::vector<Token> token_list;
		int line_no = 0;
		int pos = 0;
		
		std::vector<std::string> str_list = split(json_str);
		
		dfa::dfa json_dfa = dfa::buildDFA();
		
		for(const std::string& line : str_list) {
			line_no++;
			pos = 1;
		
			auto base = line.begin();
			auto curr = line.begin();
			
			int pre_s = 0;
			int state = 0;
			
			while(base != line.end()) {
				pre_s = state;
				state = (curr != line.end()) ? json_dfa.transition(state, *curr) : -1;
				
				if(state == -1) {
					if(!json_dfa.isAccepted(pre_s)) 
						throw TokenizeFailedException(line_no, pos);
						
					token_list.push_back({
						getType(pre_s),
						std::string(base, curr)
					});
					
					state = 0;
					base = curr;
				}
				else {
					curr++;
					pos++;
				}
			}
		}

		return remove_whitespace(token_list);
	}
}
