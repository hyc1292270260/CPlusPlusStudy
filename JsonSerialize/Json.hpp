#pragma once
#include "JsonHelper.h"
using namespace JSON;
class JSONHelp
{
public:
	static JSONValue* Parse(const char* content)
	{
		if (!content)
			return nullptr;

		JSON::skipIgnoreCharacter(content);
		return JSONValue::Parse(content);
	};
};
