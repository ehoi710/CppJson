#include "CppJsonParser.h"

namespace cppjson {
	void consume(token_iterator& cur, TokenType type) {
		if (cur->type != type) throw ("Token type is not " + toString(type)); cur++;
	}

	std::shared_ptr<JsonBase> parse(const std::vector<Token>& token_list) {
		auto beg = token_list.begin();
		return parse_element(beg);
	}

	std::shared_ptr<JsonBase> parse_element(token_iterator& cur) {
		switch (cur->type) {
		case TokenType::LBRACE: return parse_object(cur);
		case TokenType::LBRACKET: return parse_array(cur);
		case TokenType::NUMBER: return parse_number(cur);
		case TokenType::STRING: return parse_string(cur);
		case TokenType::BOOLEAN: return parse_boolean(cur);
		case TokenType::T_NULL: return parse_null(cur);
		}

		throw 0xFFFFFFFB;
	}

	std::shared_ptr<JsonNumber> parse_number(token_iterator& cur) {
		consume(cur, TokenType::NUMBER);
		return std::shared_ptr<JsonNumber>(new JsonNumber((cur - 1)->value));
	}

	std::shared_ptr<JsonString> parse_string(token_iterator& cur) {
		consume(cur, TokenType::STRING);
		const std::string& value = (cur - 1)->value;
		std::string str(value.begin() + 1, value.end() - 1);
		return std::shared_ptr<JsonString>(new JsonString(str));
	}

	std::shared_ptr<JsonBoolean> parse_boolean(token_iterator& cur) {
		consume(cur, TokenType::BOOLEAN);
		return std::shared_ptr<JsonBoolean>(new JsonBoolean((cur - 1)->value));
	}

	std::shared_ptr<JsonObject> parse_object(token_iterator& cur) {
		consume(cur, TokenType::LBRACE);
		if (cur->type == TokenType::RBRACE) return std::shared_ptr<JsonObject>(new JsonObject());

		std::vector<object_entry> map;

		std::shared_ptr<JsonString> str = parse_string(cur);
		consume(cur, TokenType::COLON);
		std::shared_ptr<JsonBase> elem = parse_element(cur);

		map.push_back(object_entry(str, elem));
		while (cur->type != TokenType::RBRACE) {
			consume(cur, TokenType::COMMA);

			str = parse_string(cur);
			consume(cur, TokenType::COLON);
			elem = parse_element(cur);

			map.push_back(object_entry(str, elem));
		}
		cur++;

		return std::shared_ptr<JsonObject>(new JsonObject(map));
	}

	std::shared_ptr<JsonArray> parse_array(token_iterator& cur) {
		consume(cur, TokenType::LBRACKET);

		if (cur->type == TokenType::RBRACKET) return std::shared_ptr<JsonArray>(new JsonArray());

		std::vector<std::shared_ptr<JsonBase>> array;

		std::shared_ptr<JsonBase> elem = parse_element(cur);
		array.push_back(elem);

		while (cur->type != TokenType::RBRACKET) {
			consume(cur, TokenType::COMMA);

			elem = parse_element(cur);
			array.push_back(elem);
		}
		cur++;

		return std::shared_ptr<JsonArray>(new JsonArray(array));
	}
	
	std::shared_ptr<JsonNull> parse_null(token_iterator& cur) {
		cur++;

		return std::shared_ptr<JsonNull>(new JsonNull);
	}
}