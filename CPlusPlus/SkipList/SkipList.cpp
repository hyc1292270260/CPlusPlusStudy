#include "SkipList.h"

SkipList::SkipList()
{
	m_head = new Node();
}

SkipList::~SkipList()
{
	if (m_head)
	{
		delete m_head;
		m_head = nullptr;
	}
}

bool SkipList::search(int target)
{
	vector<Node*> preVector(MAX_LEVEL);
	findClosedNodes(target, preVector, MAX_LEVEL);
	//��0�㵥������
	auto p = preVector[0]->next[0];
	return p && p->value == target;
}

void SkipList::add(int value)
{
	int level = getRandomLevel();
	vector<Node*> preVector(level);
	findClosedNodes(value, preVector, level);
	auto p = new Node(value);
	for (int i = 0; i < level; i++) {
		p->next[i] = preVector[i]->next[i];
		preVector[i]->next[i] = p;
	}
}

bool SkipList::erase(int value)
{
	vector<Node*> preVector(MAX_LEVEL);
	findClosedNodes(value, preVector, MAX_LEVEL);
	auto p = preVector[0]->next[0];
	//��0�㵥�����Ҳ�������û��
	if (!p || p->value != value) return false;

	for (int i = 0; i < MAX_LEVEL; i++) {
		if (preVector[i]->next[i] == p)
		{
			preVector[i]->next[i] = p->next[i];
		}
	}
	delete p;
	p = nullptr;
	return true;
}

// ����level��С��target�����ڵ�
void SkipList::findClosedNodes(int target, vector<Node*>& preVector, int level)
{
	auto p = m_head;
	for (int i = level - 1; i >= 0; --i)
	{
		while (p->next[i] && p->next[i]->value < target)
			p = p->next[i];
		preVector[i] = p;
	}
}

//�÷������������ 1~MAX_LEVEL ֮�����:
//        1/2 �ĸ��ʷ��� 1
//        1/4 �ĸ��ʷ��� 2
//        1/8 �ĸ��ʷ��� 3 �Դ�����
int SkipList::getRandomLevel() {
	int level = 1;
	while (1.f * rand() / RAND_MAX < SKIPLIST_P && level < MAX_LEVEL)
		level += 1;
	return level;
}
