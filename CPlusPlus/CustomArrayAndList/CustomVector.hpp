#pragma once
#include <iostream>
using namespace std;
constexpr int DEFAULT_CAPACITY = 8;

template<class T>
class CustomVector {
public:
	CustomVector<T>();
	~CustomVector<T>();

	void reserve(int capcity);
	void push(const T& value);
	void clear();
	void insert(const T& value, int pos);
	T pop();
	bool remove(int pos);
	int findIndex(const T& value) const;
	int capacity() const;
	int size() const;
	bool empty() const;
	void reverse();
	void printAll() const;
	T operator[](int index) const;
private:
	void expandCapacity();

	T* m_data;
	int m_size;
	int m_capacity;
};


template<class T>
CustomVector<T>::CustomVector()
{
	m_size = 0;
	m_capacity = DEFAULT_CAPACITY;
	m_data = new T[m_capacity];
}

template<class T>
CustomVector<T>::~CustomVector()
{
	m_capacity = m_size = 0;
	delete[] m_data;
	m_data = nullptr;
}

template<class T>
void CustomVector<T>::reserve(int capacity)
{
	if (m_capacity <= capacity)
		return;

	m_capacity = capacity;
}

template<class T>
void CustomVector<T>::push(const T& value)
{
	if (m_size >= m_capacity)
		expandCapacity();
	m_data[m_size++] = value;
}

template<class T>
void CustomVector<T>::clear()
{
	while (!empty())
		pop();
}

template<class T>
void CustomVector<T>::insert(const T& value, int pos)
{
	if (pos >= m_size)
		return;

	if (m_size++ >= m_capacity)
		expandCapacity();
	for (int i = m_size; i > pos; --i)
		m_data[i] = m_data[i - 1];

	m_data[pos] = value;
}

template<class T>
T CustomVector<T>::pop()
{
	return m_data[m_size--];
}

template<class T>
bool CustomVector<T>::remove(int pos)
{
	if (m_size <= 0 || pos >= m_size || pos < 0)
		return false;

	for (int i = pos; i < m_size - 1; ++i)
		m_data[i] = m_data[i + 1];
	--m_size;
	return true;
}

template<class T>
int CustomVector<T>::capacity() const
{
	return m_capacity;
}

template<class T>
int CustomVector<T>::findIndex(const T& value) const
{
	for (int i = 0; i < m_size; ++i)
	{
		if (m_data[i] == value)
			return i;
	}
	return -1;
}

template<class T>
int CustomVector<T>::size() const
{
	return m_size;
}

template<class T>
bool CustomVector<T>::empty() const
{
	return m_size == 0;
}

template<class T>
void CustomVector<T>::reverse()
{
	T* oldData = m_data;
	m_data = new T[m_capacity];
	for (int i = 0; i < m_size; ++i)
		m_data[i] = oldData[m_size - i];
	delete[]oldData;
	oldData = nullptr;
}

template<class T>
void CustomVector<T>::printAll() const
{
	cout << "print all ";
	for (int i = 0; i < m_size; ++i)
	{
		cout << m_data[i] << "   ";
		if (i == m_size - 1)
			cout << endl;
	}
}

template<class T>
inline T CustomVector<T>::operator[](int index) const
{
	return m_data[index];
}

template<class T>
void CustomVector<T>::expandCapacity()
{
	m_capacity *= 2;
	T* oldData = m_data;
	m_data = new T[m_capacity];
	for (int i = 0; i < m_size; ++i)
		m_data[i] = oldData[i];
	delete[]oldData;
	oldData = nullptr;
}