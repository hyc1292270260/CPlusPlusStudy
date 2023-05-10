#pragma once
template<class T>
struct Node
{
	T data;
	Node<T>* pNext;
	Node<T>* pPre;

	Node(const T& data, Node<T>* pNext = nullptr, Node<T>* pPre = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
		this->pPre = pPre;
	}

	bool operator !()
	{
		return this == nullptr;
	}

};

template<class T>
class CustomList {
public:
	CustomList<T>();
	~CustomList<T>();

	Node<T>* push(T value);
	Node<T>* insert(Node<T>* insertNode, const T& value);
	Node<T>* find(const T& value);
	void remove(const Node<T>* node);
	void popAll();
	void printAll();
private:
	Node<T>* m_pHead;
	Node<T>* m_pTail;

};

template<class T>
CustomList<T>::CustomList()
{

}

template<class T>
CustomList<T>::~CustomList()
{
	if (m_pHead)
	{
		while (m_pHead->pNext)
		{
			m_pHead = m_pHead->pNext;
			delete m_pHead->pPre;
			m_pHead->pPre = nullptr;
		}
		delete m_pHead;
		m_pHead = nullptr;
	}
}

template<class T>
Node<T>* CustomList<T>::push(T value)
{
	if (!m_pHead)
	{
		m_pTail = m_pHead = new Node<T>(value);

	}
	else if (!m_pHead->pNext)
	{
		m_pTail = new Node<T>(value);
		m_pHead->pNext = m_pTail;
		m_pTail->pPre = m_pHead;
	}
	else
	{
		Node<T>* newNode = new Node<T>(value);
		newNode->pPre = m_pTail;
		m_pTail->pNext = newNode;
		m_pTail = newNode;
	}
	return m_pHead;
}

template<class T>
Node<T>* CustomList<T>::insert(Node<T>* insertNode, const T& value)
{
	if (insertNode == nullptr || m_pHead == nullptr) return nullptr;

	auto newNode = new Node<T>(value);
	newNode->pNext = insertNode->pNext;
	insertNode->pNext = newNode;
	if (insertNode == m_pTail)
		newNode = m_pTail;
	else
		newNode->pNext->pPre = newNode;
	return m_pHead;
}

template<class T>
Node<T>* CustomList<T>::find(const T& value)
{
	Node<T>* pTempNode = m_pHead;
	while (pTempNode)
	{
		if (pTempNode->data == value)
			return pTempNode;
		else
			pTempNode = pTempNode->pNext;
	}
	return nullptr;
}

template<class T>
void CustomList<T>::remove(const Node<T>* node)
{
	if (m_pHead == nullptr) return;

	Node<T>* pNode = m_pHead;
	while (pNode)
	{
		if (pNode == node)
		{
			pNode->pNext->pPre = pNode->pPre;
			if (pNode->pPre)
			{
				pNode->pPre->pNext = pNode->pNext;
				pNode->pPre = nullptr;
			}
			else
			{
				m_pHead = pNode->pNext;
			}

			pNode->pNext = nullptr;
			delete pNode;
			pNode = nullptr;
		}
		else
		{
			pNode = pNode->pNext;
		}
	}
}

template<class T>
void CustomList<T>::popAll()
{
	while (m_pHead->pNext)
	{
		m_pHead = m_pHead->pNext;
		delete m_pHead->pPre;
		m_pHead->pPre = nullptr;
	}
	if (m_pHead)
	{
		delete m_pHead;
		m_pHead = nullptr;
	}
}

template<class T>
void CustomList<T>::printAll()
{
	std::cout << "print all ";
	if (m_pHead == nullptr) return;

	for (Node<T>* node = m_pHead; node != nullptr; node = node->pNext)
	{
		std::cout << node->data << "  ";
	}
	std::cout << endl;
}
