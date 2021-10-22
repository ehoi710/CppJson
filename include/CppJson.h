#ifndef __CPPJSON__
#define __CPPJSON__

#include <stdio.h>
#include <fstream>

#include "CppJsonBase.h"
#include "CppJsonLexer.h"
#include "CppJsonParser.h"

namespace cppjson {
	class Json {
	public:
		Json();
		Json(JsonBase* json);
		~Json();

		operator std::string();
		operator double();
		operator bool();

		Json operator[](const char* key);
		Json operator[](std::string key);
		Json operator[](int idx);

		Json& operator=(JsonBase* json);
		
		std::string toString() const;
		
		static Json loadFromFile(std::string file_name);

	private:
		JsonBase* json;
	};
}

std::ostream& operator<<(std::ostream& os, const cppjson::JsonBase& json);
std::ostream& operator<<(std::ostream& os, const cppjson::Json& json);

#endif
