#include <string>
#include <fstream>
#include "SensitiveWordHelper.h"

void SensitiveWordHelper::load(const char* fileName)
{
	std::ifstream fin(fileName);
	std::string line;
	while (getline(fin, line))
	{
		addNewNode(line.c_str());
	}

	fin.close();
}

void SensitiveWordHelper::addNewNode(const char* word)
{
	if (!word)
		return;

	if (m_root == nullptr)
	{
		m_root = new WordNode(word);
	}
	else
	{
		WordNode* findNode = m_root;
		while (findNode->next)
		{
			findNode = findNode->next;
		}
		findNode->next = new WordNode(word);
	}

}

bool SensitiveWordHelper::check(const char* word)
{
	if (!word)
		return false;

	WordNode* node = m_root;
	while (node)
	{
		if (strcmp(node->word, word) == 0)
			return true;
		node = node->next;
	}
	return false;
}