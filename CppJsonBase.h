#ifndef __CPPJSON__
#define __CPPJSON__

namespace cppjson {
class JsonElement { };

class JsonObject  : public JsonElement { };
class JsonArray   : public JsonElement { };
class JsonString  : public JsonElement { };
class JsonNumber  : public JsonElement { };
class JsonBoolean : public JsonElement { };
}

#endif