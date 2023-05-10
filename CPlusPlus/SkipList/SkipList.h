#pragma once
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;

const unsigned int MAX_LEVEL = 32;  //�����������
const float SKIPLIST_P = 0.25;  //��������
const unsigned int DEFAULT_VALUE = -1;  //Ĭ��ֵ

struct Node
{
	int value;
	vector<Node*> next;
	Node(int value) :value(value)
	{
		next.resize(MAX_LEVEL, nullptr);
	}

	Node()
	{
		next.resize(MAX_LEVEL, nullptr);
		value = DEFAULT_VALUE;
	}
};

class SkipList
{
public:
	SkipList();
	~SkipList();

	bool search(int target);
	void add(int value);
	bool erase(int value);

private:
	void findClosedNodes(int target, vector<Node*>& pre, int level);
	int getRandomLevel();
	Node* m_head = nullptr;//ͷ���
};

