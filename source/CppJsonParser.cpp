#include "CppJsonParser.h"

namespace cppjson {
	void consume(token_iterator& cur, TokenType type) {
		if (cur->type != type) 
			throw ParsingFailedException(
				cur->line, cur->pos, 
				std::string("unexpected token " + toString(cur->type) + 
				            " founded instead " + toString(type))
			); 
			
		cur++;
	}

	JsonBase* parse(const std::vector<Token>& token_list) {
		auto beg = token_list.begin();
		return parse_element(beg);
	}

	JsonBase* parse_element(token_iterator& cur) {
		switch (cur->type) {
		case TokenType::LBRACE:   return parse_object(cur);
		case TokenType::LBRACKET: return parse_array(cur);
		case TokenType::NUMBER:   return parse_number(cur);
		case TokenType::STRING:   return parse_string(cur);
		case TokenType::BOOLEAN:  return parse_boolean(cur);
		case TokenType::T_NULL:   return parse_null(cur);
		}

		throw 0xFFFFFFFB;
	}

	JsonNumber* parse_number(token_iterator& cur) {
		consume(cur, TokenType::NUMBER);
		return new JsonNumber((cur - 1)->value);
	}

	JsonString* parse_string(token_iterator& cur) {
		consume(cur, TokenType::STRING);
		const std::string& value = (cur - 1)->value;
		std::string str(value.begin() + 1, value.end() - 1);
		return new JsonString(str);
	}

	JsonBoolean* parse_boolean(token_iterator& cur) {
		consume(cur, TokenType::BOOLEAN);
		return new JsonBoolean((cur - 1)->value);
	}

	JsonObject* parse_object(token_iterator& cur) {
		consume(cur, TokenType::LBRACE);
		if (cur->type == TokenType::RBRACE) {
			cur++;
			return new JsonObject();
		}

		std::vector<object_entry> map;

		JsonString* str = parse_string(cur);
		consume(cur, TokenType::COLON);
		JsonBase* elem = parse_element(cur);

		map.push_back(object_entry(str, elem));
		
		while (cur->type != TokenType::RBRACE) {
			consume(cur, TokenType::COMMA);

			str = parse_string(cur);
			consume(cur, TokenType::COLON);
			elem = parse_element(cur);

			map.push_back(object_entry(str, elem));
		}
		cur++;

		return new JsonObject(map);
	}

	JsonArray* parse_array(token_iterator& cur) {
		consume(cur, TokenType::LBRACKET);
		if (cur->type == TokenType::RBRACKET) {
			cur++;
			return new JsonArray();
			
		}

		std::vector<JsonBase*> array;

		JsonBase* elem = parse_element(cur);
		array.push_back(elem);

		while (cur->type != TokenType::RBRACKET) {
			consume(cur, TokenType::COMMA);

			elem = parse_element(cur);
			array.push_back(elem);
		}
		cur++;

		return new JsonArray(array);
	}
	
	JsonNull* parse_null(token_iterator& cur) {
		cur++;

		return new JsonNull;
	}
}
