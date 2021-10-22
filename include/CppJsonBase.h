#ifndef __CPPJSONBASE__
#define __CPPJSONBASE__

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "CppJsonException.h"

namespace cppjson {

	class JsonBase {
	public:
		virtual ~JsonBase() {}

		virtual std::string toString() const { throw NotImplementedException(); }
		virtual double toNumber() const { throw NotImplementedException(); }
		virtual bool toBoolean() const { throw NotImplementedException(); }
		virtual JsonBase* find(std::string key) const { throw NotImplementedException(); }
		virtual JsonBase* get(size_t idx) const { throw NotImplementedException(); }
	};

	class JsonString : public JsonBase {
	public:
		JsonString();
		JsonString(std::string str);

		std::string toString() const;

	private:
		std::string str;
	};

	class JsonNumber : public JsonBase {
	public:
		JsonNumber();
		JsonNumber(double num);
		JsonNumber(std::string num);

		double toNumber() const;
		std::string toString() const;

	private:
		double num;
	};

	class JsonBoolean : public JsonBase {
	public:
		JsonBoolean();
		JsonBoolean(std::string boolean);

		bool toBoolean() const;
		std::string toString() const;

	private:
		bool boolean;
	};

	class JsonObject : public JsonBase {
	public:
		using Entry = std::pair<JsonString*, JsonBase*>;

	public:
		JsonObject();
		JsonObject(std::vector<Entry> map);

		~JsonObject();

		JsonBase* find(std::string key) const;
		std::string toString() const;

	private:
		std::unordered_map<std::string, JsonBase*> map;
	};

	class JsonArray : public JsonBase {
	public:
		JsonArray();
		JsonArray(std::vector<JsonBase*> array);

		~JsonArray();

		JsonBase* get(size_t idx) const;
		std::string toString() const;

	private:
		std::vector<JsonBase*> array;
	};

	class JsonNull : public JsonBase {
	public:
		JsonNull();

		std::string toString() const;
	};
}

#endif
