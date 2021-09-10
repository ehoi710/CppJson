#ifndef __CPPJSON__
#define __CPPJSON__

#include <string>
#include <vector>

#include "CppJsonBase.h"
#include "CppJsonLexer.h"
#include "CppJsonParser.h"

namespace cppjson {
	class Json {
	public:
		Json(std::string json_str);
		Json(std::shared_ptr<JsonBase> json);

		operator std::string();
		operator double();
		operator bool();

		Json operator[](const char* key);
		Json operator[](std::string key);
		Json operator[](int idx);

		Json& operator=(std::shared_ptr<JsonBase> json);
		
		std::string toString() const;

	private:
		std::shared_ptr<JsonBase> json;
	};
}

std::ostream& operator<<(std::ostream& os, const cppjson::JsonBase& json);
std::ostream& operator<<(std::ostream& os, const cppjson::Json& json);

#endif
