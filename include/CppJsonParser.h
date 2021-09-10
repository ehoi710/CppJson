#ifndef __CPPJSONPARSER__
#define __CPPJSONPARSER__

#include <iostream>
#include <stack>
#include <vector>

#include "CppJsonBase.h"
#include "CppJsonLexer.h"

namespace cppjson {
	using token_iterator = std::vector<Token>::const_iterator;
	using object_entry = JsonObject::Entry;
	
	std::shared_ptr<JsonBase> parse(const std::vector<Token>& token_list);
	std::shared_ptr<JsonBase> parse_element(token_iterator& cur);

	void consume(token_iterator& cur, TokenType type);

	std::shared_ptr<JsonNumber> parse_number(token_iterator& cur);
	std::shared_ptr<JsonString> parse_string(token_iterator& cur);
	std::shared_ptr<JsonBoolean> parse_boolean(token_iterator& cur);
	std::shared_ptr<JsonObject> parse_object(token_iterator& cur);
	std::shared_ptr<JsonArray> parse_array(token_iterator& cur);
	std::shared_ptr<JsonNull> parse_null(token_iterator& cur);
}

#endif