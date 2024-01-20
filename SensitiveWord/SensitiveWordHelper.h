#pragma once
#include <string.h>
using namespace std;

struct WordNode {
	WordNode(const char* word)
	{
		int length = strlen(word) + 1;
		this->word = new char[length];
		memcpy(this->word, word, length);
		next = nullptr;
	}
	char* word;
	WordNode* next;
};

class SensitiveWordHelper
{
public:
	void load(const char* fileName);
	bool check(const char* word);

private:
	WordNode* m_root = nullptr;
	void addNewNode(const char* word);

};
