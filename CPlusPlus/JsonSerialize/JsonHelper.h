#pragma once
#include <string>
#include <vector>
#include <map>

namespace JSON
{
	enum EJSONValueType
	{
		VALUE_TYPE_INT = 0,
		VALUE_TYPE_FLOAT = 1,
		VALUE_TYPE_BOOL = 2,
		VALUE_TYPE_STRING = 3,
		VALUE_TYPE_NULL = 4,
		VALUE_TYPE_ARRAY = 5,
		VALUE_TYPE_OBJECT = 6
	};

	// Ìø¹ýºöÂÔ×Ö·û
	extern void skipIgnoreCharacter(const char*& content);
	// ×Ö·ûÊÇ·ñÏàµÈ
	extern bool checkCharEqual(const char* str, const char* target, int len);
	// ÌáÈ¡×Ö·û´®
	extern bool extractString(const char*& content, std::string& out);

	class JSONValue;
	typedef std::vector<JSONValue*> JSONArray;
	typedef std::map<std::string, JSONValue*> JSONObject;
	typedef JSONValue* (*ParseFunc)(const char*&);

	class JSONValue
	{
	public:
		static JSONValue* Parse(const char*&);
		static JSONValue* ParseByOpt(const char*&);
		static JSONValue* ParseObject(const char*&);
		static JSONValue* ParseArray(const char*&);
		static JSONValue* ParseNumber(const char*&);
		static JSONValue* ParseBool(const char*&);
		static JSONValue* ParseNull(const char*&);
		static JSONValue* ParseString(const char*&);
		static const std::map<char, ParseFunc> optMap;

		JSONValue();
		JSONValue(bool);
		JSONValue(int);
		JSONValue(float);
		JSONValue(std::string);
		JSONValue(JSONObject&);
		JSONValue(JSONArray&);
		~JSONValue();

		inline bool IsObject() const { return m_type == EJSONValueType::VALUE_TYPE_OBJECT; };
		inline bool IsString() const { return m_type == EJSONValueType::VALUE_TYPE_STRING; };
		inline bool IsNull() const { return m_type == EJSONValueType::VALUE_TYPE_NULL; };
		inline bool IsArray() const { return m_type == EJSONValueType::VALUE_TYPE_ARRAY; };
		inline bool IsInt() const { return m_type == EJSONValueType::VALUE_TYPE_INT; };
		inline bool IsFloat() const { return m_type == EJSONValueType::VALUE_TYPE_FLOAT; };

		inline const JSONObject& AsObject() const { return *m_data.ObjectValue; };
		inline const std::string& AsString() const { return *m_data.StringValue; };
		inline const bool AsBool() const { return m_data.BoolValue; };
		inline const JSONArray& AsArray() const { return *m_data.ArrayValue; };

		inline const EJSONValueType GetValueType() const { return m_type; };;

		std::string Stringify() const;
		std::vector<std::string> ObjectKeys() const;
		JSONValue* Child(const char* Key) const;

	private:
		EJSONValueType m_type;
		union JSONData
		{
			int IntValue;
			float FloatValue;
			bool BoolValue;
			std::string* StringValue;
			JSONObject* ObjectValue;
			JSONArray* ArrayValue;
		}m_data;
	};
}


