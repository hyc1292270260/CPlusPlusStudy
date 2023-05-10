#include "CustomString.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	auto str1 = CustomString("test1");
	cout << "str1: " << str1 << " str1[1]: " << str1[1] << " str1.len: " << str1.len() << endl;
	CustomString str2 = CustomString("test2, test3");
	CustomString sub1 = str1.sub(1, 2);
	cout << "str1Sub" << sub1 << endl;
	str1 = "test111";
	CustomString str3 = str2;
	cout << "str1: " << str1 << " str2: " << str2 << "str3:" << str3 << endl;
	str1.append("append");
	cout << "str1append: " << str1 << endl;
	bool equal1 = str1 == str2;
	bool equal2 = str2 == "test2, test3";
	int index = str1.find("st");
	cout << equal1 << "___" << equal2 << "___" << index << endl;
	str2 = "tes,st2,,, tes,t3,";
	auto customStringVec = str2.split(",");
	for (auto iter = customStringVec.begin(); iter != customStringVec.end(); iter++)
		cout << (*iter) << endl;
	customStringVec = str2.split("es");
	for (auto iter = customStringVec.begin(); iter != customStringVec.end(); iter++)
		cout << (*iter) << endl;

	return 0;
}