#include "SensitiveWordHelper.h"
#include <iostream>
using namespace std;

int main()
{
	SensitiveWordHelper helper;
	helper.load("SensitiveWord.txt");
	cout << helper.check("fuck") << endl;
	cout << helper.check("aaa") << endl;
	cout << helper.check("woc") << endl;

	return 0;
}