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
	//第0层单链表找
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
	//第0层单链表找不到就是没有
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

// 查找level层小于target的最大节点
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

//该方法会随机生成 1~MAX_LEVEL 之间的数:
//        1/2 的概率返回 1
//        1/4 的概率返回 2
//        1/8 的概率返回 3 以此类推
int SkipList::getRandomLevel() {
	int level = 1;
	while (1.f * rand() / RAND_MAX < SKIPLIST_P && level < MAX_LEVEL)
		level += 1;
	return level;
}
