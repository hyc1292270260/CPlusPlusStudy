#include <iostream>
#include<string>
using namespace std;
class MyString 
{
	friend std::ostream& operator << (std::ostream&os, MyString& str);
	friend std::istream& operator >> (std::istream&is, MyString& str);
public:
	MyString(const char *str)
	{
		int length = strlen(str);
		_pStr = new char[length + 1];
		if (_pStr)
			strcpy_s(_pStr,length+1, str);
	
	}
	MyString():_pStr(nullptr)
	{

	}
	~MyString()
	{
		if (_pStr)
		{
			delete[] _pStr;
			_pStr = nullptr;
		}
	
	
	}
	void show(void) const
	{
		cout << _pStr << endl;
	
	}
	char& operator[](const int index)
	{
		return _pStr[index];
	}
	bool operator == (MyString& other)
	{
		return  strcmp(_pStr, other._pStr) == 0;
	}
	bool operator == (const char*other)
	{
		return  strcmp(_pStr, other) == 0;
	}
	operator bool()
	{
		return _pStr;
	}
	MyString& operator + (MyString& other)
	{
		auto length = strlen(_pStr);
		auto other_length = strlen(other._pStr);
		char* pStr = new char[length + other_length + 1];
		if (pStr)
		{
			strcpy_s(pStr, length + 1, _pStr);
			strcat_s(pStr, length + other_length + 1, other._pStr);
			delete[] _pStr;
			_pStr = pStr;
		}
		return *this;
	
	}
	MyString& operator + (const char* other)
	{
		auto length = strlen(_pStr);
		auto other_length = strlen(other);
		char* pStr = new char[length + other_length + 1];
		if (pStr)
		{
			strcpy_s(pStr, length + 1, _pStr);
			strcat_s(pStr, length + other_length + 1, other);
			delete[] _pStr;
			_pStr = pStr;
		}
		return *this;

	}
	MyString& operator=(MyString& other)
	{
		if (!other._pStr)
			return *this;
		if (_pStr)
			delete[] _pStr;
		int length = strlen(other._pStr);
		_pStr = new char[length + 1];
		strcpy_s(_pStr, length + 1, other._pStr);
		return *this;
	}
	MyString& operator=(const char* other)
	{
		if (!other)
			return *this;
		if (_pStr)
			delete[] _pStr;
		int length = strlen(other);
		_pStr = new char[length + 1];
		strcpy_s(_pStr, length + 1, other);
		return *this;
	}
private: 
	char *_pStr;
};
std::ostream& operator << (std::ostream&os,MyString& str)
{
	os << str._pStr;
	return os;
}
std::istream& operator >> (std::istream&is, MyString& str)
{
	is >> str._pStr;
	return is;
}
int main(void)
{
	MyString str("Hello");
	cout << str[2] << endl;
	MyString str1("HEllo");
	MyString str2("Hi");
	bool result = (str == str1);
	bool result1 = (str == "Hello");
	str = str2 + str1;
	MyString str3;
	str.show();
	str3 = str;
	str3.show();
	cin >> str;
	cout << str << endl;
	

	
	return 0;


}