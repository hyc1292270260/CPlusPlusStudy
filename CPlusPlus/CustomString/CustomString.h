#pragma once
#include <iostream>
#include <vector>
class CustomString {
	friend std::ostream& operator << (std::ostream& os, CustomString& str);
	friend std::istream& operator >> (std::istream& is, CustomString& str);
public:
	CustomString(const char* str = nullptr);
	CustomString(const CustomString& other);
	~CustomString();

	CustomString sub(int start, int len);
	void append(const char* str);
	int len() const;
	int find(const char* subStr) const;
	std::vector<CustomString> split(const char* sep);
	bool operator==(CustomString& otherStr);
	bool operator==(const char* otherStr);
	char& operator[](const int index) const;
	CustomString& operator=(const CustomString& otherStr);
	CustomString& operator=(const char* otherStr);
	bool operator!() const;

private:
	int calcLen(const char* str);
	void strCopy(char* tar, const char* src);
	void reset();
	char* m_str = nullptr;
	int m_len = 0;
};

