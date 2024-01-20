#include "JsonHelper.h"
#include <iostream>

namespace JSON
{
	const std::map<char, ParseFunc> JSONValue::optMap =
	{
		{'"',JSONValue::ParseString},
		{'{',JSONValue::ParseObject},
		{'[',JSONValue::ParseArray},
		{'n',JSONValue::ParseNull},
		{'N',JSONValue::ParseNull},
		{'f',JSONValue::ParseBool},
		{'F',JSONValue::ParseBool},
		{'t',JSONValue::ParseBool},
		{'T',JSONValue::ParseBool},
		{'0',JSONValue::ParseNumber},
		{'1',JSONValue::ParseNumber},
		{'2',JSONValue::ParseNumber},
		{'3',JSONValue::ParseNumber},
		{'4',JSONValue::ParseNumber},
		{'5',JSONValue::ParseNumber},
		{'6',JSONValue::ParseNumber},
		{'7',JSONValue::ParseNumber},
		{'8',JSONValue::ParseNumber},
		{'9',JSONValue::ParseNumber},
		{'+',JSONValue::ParseNumber},
		{'-',JSONValue::ParseNumber},
		{'.',JSONValue::ParseNumber},
	};

	void skipIgnoreCharacter(const char*& content)
	{
		while (*content != 0 && (*content == ' ' || *content == '\n' || *content == '\r' || *content == '\t'))
			content++;
	}

	bool checkCharEqual(const char* str, const char* target, int len)
	{
		if (!str && !target)	return true;
		if (!str || !target || len <= 0)	return false;
		for (int i = 0; i < len; ++i)
		{
			if (*(str + i) != *(target + i))
				return false;
		}
		return true;
	}

	bool extractString(const char*& content, std::string& out)
	{
		// 跳过第一个"
		content++;
		while (*content != 0)
		{
			if (*content == '"')
			{
				content++;
				return true;
			}
			out += *content;
			content++;
		}
		return false;
	}

	JSONValue::JSONValue()
	{
		m_type = EJSONValueType::VALUE_TYPE_NULL;
	}

	JSONValue::JSONValue(bool value)
	{
		m_type = EJSONValueType::VALUE_TYPE_BOOL;
		m_data.BoolValue = value;
	}

	JSONValue::JSONValue(int value)
	{
		m_type = EJSONValueType::VALUE_TYPE_INT;
		m_data.IntValue = value;
	}

	JSONValue::JSONValue(float value)
	{
		m_type = EJSONValueType::VALUE_TYPE_FLOAT;
		m_data.FloatValue = value;
	}

	JSONValue::JSONValue(std::string str)
	{
		m_type = EJSONValueType::VALUE_TYPE_STRING;
		m_data.StringValue = new std::string(str);
	}

	JSONValue::JSONValue(JSONObject& object)
	{
		m_type = EJSONValueType::VALUE_TYPE_OBJECT;
		m_data.ObjectValue = new JSONObject(object);
	}

	JSONValue::JSONValue(JSONArray& value)
	{
		m_type = EJSONValueType::VALUE_TYPE_ARRAY;
		m_data.ArrayValue = new JSONArray(value);
	}

	JSONValue::~JSONValue()
	{
		switch (m_type)
		{
		case EJSONValueType::VALUE_TYPE_OBJECT:
		{
			for (JSONObject::iterator it = m_data.ObjectValue->begin(); it != m_data.ObjectValue->end(); it++)
				delete it->second;
			delete m_data.ObjectValue;
			break;
		}
		case EJSONValueType::VALUE_TYPE_ARRAY:
		{
			for (JSONArray::iterator it = m_data.ArrayValue->begin(); it != m_data.ArrayValue->end(); it++)
				delete* it;
			delete m_data.ArrayValue;
			break;
		}
		case EJSONValueType::VALUE_TYPE_STRING:
		{
			delete m_data.StringValue;
		}
		m_type = EJSONValueType::VALUE_TYPE_NULL;
		}
	}

	std::string JSONValue::Stringify() const
	{
		std::string result;
		switch (m_type)
		{
		case(EJSONValueType::VALUE_TYPE_INT):
			result = std::to_string(m_data.IntValue);
			break;
		case(EJSONValueType::VALUE_TYPE_FLOAT):
			result = std::to_string(m_data.FloatValue);
			break;
		case EJSONValueType::VALUE_TYPE_NULL:
			result = "null";
			break;
		case EJSONValueType::VALUE_TYPE_BOOL:
			result = m_data.BoolValue ? "true" : "false";
			break;
		case EJSONValueType::VALUE_TYPE_STRING:
			result = *m_data.StringValue;
			break;
		case EJSONValueType::VALUE_TYPE_ARRAY:
		{
			result += "[";
			auto it = m_data.ArrayValue->begin();
			while (it != m_data.ArrayValue->end())
			{
				result += (*it)->Stringify();
				if (++it != m_data.ArrayValue->end())
					result += ",";
			}
			result += "]";
			break;
		}
		case EJSONValueType::VALUE_TYPE_OBJECT:
		{
			result += "{";
			auto it = m_data.ObjectValue->begin();
			while (it != m_data.ObjectValue->end())
			{
				result += it->first;
				result += ":";
				result += it->second->Stringify();
				if (++it != m_data.ObjectValue->end())
					result += ",";
			}
			result += "}";
			break;
		}
		}
		return result;
	}

	std::vector<std::string> JSONValue::ObjectKeys() const
	{
		std::vector<std::string> keys;
		if (m_type == EJSONValueType::VALUE_TYPE_OBJECT)
		{
			JSONObject::const_iterator iter = m_data.ObjectValue->begin();
			while (iter != m_data.ObjectValue->end())
				keys.push_back(iter++->first);
		}
		return keys;
	}

	JSONValue* JSONValue::Child(const char* key) const
	{
		if (m_type != EJSONValueType::VALUE_TYPE_OBJECT)
			return nullptr;

		JSONObject::const_iterator it = m_data.ObjectValue->find(key);
		if (it != m_data.ObjectValue->end())
			return it->second;
		else
			return nullptr;
	}

	JSONValue* JSONValue::Parse(const char*& content)
	{
		JSONValue* value = ParseByOpt(content);
		return value;
	}

	JSONValue* JSONValue::ParseByOpt(const char*& content)
	{
		JSONValue* value = nullptr;
		while (*content != 0)
		{
			auto it = optMap.find(*content);
			if (it != optMap.end())
				return it->second(content);
			content++;
		}
		return nullptr;
	}

	JSONValue* JSONValue::ParseObject(const char*& content)
	{
		JSONObject object;
		while (*content != 0)
		{
			content++;
			skipIgnoreCharacter(content);
			if (*content == '}')
			{
				content++;
				return new JSONValue();
			}

			std::string objectName;
			if (!extractString(content, objectName))
				return nullptr;

			skipIgnoreCharacter(content);
			if (*(content++) != ':')
				return nullptr;

			skipIgnoreCharacter(content);
			JSONValue* value = ParseByOpt(content);
			if (value == nullptr)
				return nullptr;

			object[objectName] = value;
			skipIgnoreCharacter(content);
			if (*content == '}')
			{
				content++;
				return new JSONValue(object);
			}
		}
		return nullptr;
	}

	JSONValue* JSONValue::ParseArray(const char*& content)
	{
		JSONArray Array;
		while (*content != 0)
		{
			content++;
			skipIgnoreCharacter(content);
			if (*content == ']')
			{
				content++;
				return new JSONValue(Array);
			}

			JSONValue* value = ParseByOpt(content);
			if (value == nullptr)
				return nullptr;

			Array.push_back(value);
			skipIgnoreCharacter(content);
			if (*content == ']')
			{
				content++;
				return new JSONValue(Array);
			}
		}
		return nullptr;
	}

	JSONValue* JSONValue::ParseNumber(const char*& content)
	{
		int symbol = *content == '-' ? -1 : 1;
		if (*content == '-' || *content == '+')
			content++;
		float value = 0;
		bool isInt = true;
		while (*content >= '0' && *content <= '9')
		{
			value = value * 10 + (*content - '0');
			content++;
		}
		// 小数部分
		if (*content == '.')
		{
			isInt = false;
			content++;
			double decimal = 0.1f;
			int decimalCount = 0;
			while (*content >= '0' && *content <= '9')
			{
				decimalCount++;
				double temp = (*content - '0') * pow(0.1, decimalCount);
				value += temp;
				content++;
			}
		}
		value *= symbol;
		if (isInt)
			return new JSONValue(int(value));
		else
			return new JSONValue(value);
	}

	JSONValue* JSONValue::ParseBool(const char*& content)
	{

		if (checkCharEqual(content, "true", 4) || checkCharEqual(content, "TRUE", 4))
		{
			content += 4;
			return new JSONValue(true);
		}
		if (checkCharEqual(content, "false", 5) || checkCharEqual(content, "FALSE", 5))
		{
			content += 5;
			return new JSONValue(false);
		}
		return nullptr;
	}

	JSONValue* JSONValue::ParseNull(const char*& content)
	{
		if (checkCharEqual(content, "null", 4) || checkCharEqual(content, "NULL", 4))
		{
			content += 4;
			return new JSONValue();
		}
		return nullptr;
	}

	JSONValue* JSONValue::ParseString(const char*& content)
	{
		std::string str;
		if (extractString(content, str))
		{
			return new JSONValue(str);
		}
		return nullptr;
	}
}

