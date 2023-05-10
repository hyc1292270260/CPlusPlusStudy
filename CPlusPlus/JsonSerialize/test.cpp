#include "Json.hpp"
#include <iostream>
const char* example = "\n{  \"name \": \"John Doe\", \"age\" : 18, \"address\" : {\"country\" : \"china\", \"zip - code\" : \"10000\"}, \"chore\" : [1, true, \"2\", null] \n}";
int main()
{
	JSONValue* value = JSONHelp::Parse(example);

	auto keys = value->ObjectKeys();
	for (auto it = keys.begin(); it != keys.end(); ++it)
		std::cout << *it << std::endl;

	auto b = value->Child("address");
	std::cout << b->GetValueType() << std::endl;

	std::string str = value->Stringify();
	std::cout << str << std::endl;
}