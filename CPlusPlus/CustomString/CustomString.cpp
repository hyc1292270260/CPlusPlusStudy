#include "CustomString.h"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
constexpr char ENDCHAR = char(0);

CustomString::CustomString(const char* str)
{
	if (str == nullptr)
		return;

	int len = calcLen(str);
	if (len <= 0)
		return;

	m_str = new char[len + 1];
	m_len = len;
	strCopy(m_str, str);
}

CustomString::CustomString(const CustomString& other)
{
	if (!other)
		return;

	m_str = new char[other.m_len + 1];
	m_len = other.m_len;
	strCopy(m_str, other.m_str);
}


CustomString::~CustomString()
{
	reset();
}

int CustomString::len() const
{
	return m_len;
}

void CustomString::reset()
{
	if (m_str)
	{
		delete[] m_str;
		m_str = nullptr;
	}
	m_len = 0;
}

int CustomString::find(const char* subStr) const
{
	if (!m_str)
		return -1;

	int i = 0, j = 0;
	while (m_str[i])
	{
		j = 0; while (m_str[i + j] == subStr[j] && subStr[j] != ENDCHAR)
		{
			++j;
			if (!subStr[j])
				return i;
		}
		++i;
	}
	return -1;
}

CustomString CustomString::sub(int start, int len)
{
	if (len <= 0)
		return CustomString("\0");
	if (len + start > m_len)
		assert("out_of_range");

	char* newStr = new char[len + 1];
	int newIndex = 0;
	for (int i = start; i < start + len; ++i)
		newStr[newIndex++] = m_str[i];
	newStr[len] = ENDCHAR;
	return CustomString(newStr);
}

void CustomString::append(const char* str)
{
	int appendLen = calcLen(str);
	int len = this->len();
	int newLen = len + appendLen;
	char* newStr = new char[newLen + 1];
	for (int i = 0; i < newLen; ++i) {
		if (i < len) {
			newStr[i] = m_str[i];
		}
		else {
			newStr[i] = str[i - len];
		}
	}
	newStr[newLen] = ENDCHAR;
	if (m_str)
		delete[] m_str;
	m_str = newStr;
}

vector<CustomString> CustomString::split(const char* sep)
{
	vector<CustomString> subStr;
	if (m_len <= 0)
		return subStr;

	int seqLen = calcLen(sep);
	CustomString tempStr = CustomString(m_str);
	while (true)
	{
		int index = tempStr.find(sep);
		if (index < 0) break;

		subStr.push_back(tempStr.sub(0, index));
		int next = index + seqLen;
		if (next == tempStr.len())
			return subStr;

		tempStr = tempStr.sub(next, tempStr.len() - next);
	}
	subStr.push_back(tempStr);
	return subStr;
}

bool CustomString::operator==(CustomString& otherStr)
{
	if (!otherStr.m_str && !m_str)
		return true;
	if (!otherStr.m_str && m_str || otherStr.m_str && !m_str)
		return false;

	int i = 0;
	while (otherStr[i] == m_str[i] && otherStr.m_str[i] != ENDCHAR) {
		if (m_str[i] != ENDCHAR) {
			++i;
		}
	}
	if (otherStr.m_str[i] == ENDCHAR) return true;
	return false;
}

bool CustomString::operator!() const
{
	return !m_str || m_len <= 0;
}

bool CustomString::operator==(const char* otherStr)
{
	if (!otherStr && !m_str)
		return true;
	if (!otherStr && m_str || otherStr && !m_str)
		return false;

	int i = 0;
	while (otherStr[i] == m_str[i] && otherStr[i] != ENDCHAR) {
		if (m_str[i] != ENDCHAR) {
			++i;
		}
	}
	if (m_str[i] == ENDCHAR) return true;
	return false;
}

char& CustomString::operator[](const int index) const
{
	return m_str[index];
}

CustomString& CustomString::operator=(const char* otherStr)
{
	reset();
	if (!otherStr)
		return *this;

	int len = calcLen(otherStr);
	m_str = new char[len + 1];
	m_len = len;
	strCopy(m_str, otherStr);
	return *this;
}

CustomString& CustomString::operator=(const CustomString& otherStr)
{
	reset();
	if (!otherStr)
		return *this;

	int len = calcLen(otherStr.m_str);
	m_str = new char[len + 1];
	m_len = len;
	strCopy(m_str, otherStr.m_str);
	return *this;
}

int CustomString::calcLen(const char* str)
{
	int len = -1;
	while (str[++len]);
	return len;
}

void CustomString::strCopy(char* tar, const char* src) {
	int len = calcLen(src);
	for (int i = 0; i < len; ++i)
		tar[i] = src[i];
	tar[len] = ENDCHAR;
}

std::ostream& operator << (std::ostream& os, CustomString& str)
{
	if (str.m_str)
		os << str.m_str;
	return os;
}

std::istream& operator >> (std::istream& is, CustomString& str)
{
	is >> str.m_str;
	return is;
}
