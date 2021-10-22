#ifndef __CPPJSONPARSER__
#define __CPPJSONPARSER__

#include <iostream>
#include <stack>
#include <vector>

#include "CppJsonBase.h"
#include "CppJsonLexer.h"
#include "CppJsonException.h"

namespace cppjson {
	using token_iterator = std::vector<Token>::const_iterator;
	using object_entry = JsonObject::Entry;
	
	JsonBase* parse(const std::vector<Token>& token_list);
	JsonBase* parse_element(token_iterator& cur);

	void consume(token_iterator& cur, TokenType type);

	JsonNumber*  parse_number(token_iterator& cur);
	JsonString*  parse_string(token_iterator& cur);
	JsonBoolean* parse_boolean(token_iterator& cur);
	JsonObject*  parse_object(token_iterator& cur);
	JsonArray*   parse_array(token_iterator& cur);
	JsonNull*    parse_null(token_iterator& cur);
}

#endif
