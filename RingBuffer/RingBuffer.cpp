#include "RingBuffer.h"
#include <vcruntime_string.h>
#include <iostream>

RingBuffer::RingBuffer(unsigned int initSize)
{
	m_size = initSize;
	m_data = new char[m_size];
}

RingBuffer::~RingBuffer()
{
	delete[] m_data;
}


void RingBuffer::write(const char* data)
{
	if (data == nullptr)	return;

	int dataLen = -1;
	while (data[++dataLen]);
	if (dataLen <= 0)	return;

	int usedLen = getUsedLen();
	int needExpandSize = dataLen - (m_size - getUsedLen());
	if (needExpandSize > 0)
	{
		expandSize(needExpandSize);
		std::cout << "expandSize" << m_size << std::endl;
	}
	if (m_write + dataLen >= m_size) {
		// ³¬³ösize
		memcpy(m_data + m_write, data, m_size - m_write);
		m_write = (m_write + dataLen - m_size) % m_size;
		memcpy(m_data, data, m_write);
	}
	else
	{
		memcpy(m_data + m_write, data, dataLen);
		m_write += dataLen;
	}
}

void RingBuffer::read(char* outValua, unsigned int len)
{
	unsigned int curUsedLen = getUsedLen();
	unsigned int needReadLen = len > curUsedLen ? curUsedLen : len;
	if (needReadLen <= 0) return;
	memcpy(outValua, m_data, needReadLen);
	m_read += needReadLen;
	if (m_read >= m_size)
		m_read %= m_size;
	shrinkSize();
}

bool RingBuffer::isEmpty()
{
	return  m_read == m_write;
}

bool RingBuffer::isFull()
{
	return m_read == (m_write + 1) % m_size;
}

void RingBuffer::clear()
{
	m_read = 0;
	m_write = 0;
}

unsigned int RingBuffer::size()
{
	return m_size;
}

unsigned int RingBuffer::getUsedLen()
{
	if (isEmpty())
	{
		return 0;
	}
	else if (isFull())
	{
		return m_size;
	}
	else
	{
		int len = m_write - m_read;
		if (len < 0)
			len += m_size;
	}
}

void RingBuffer::expandSize(int needExpandSize)
{
	unsigned int usedLen = getUsedLen();
	unsigned int size = m_size;
	while (needExpandSize > 0)
	{
		m_size *= 2;
		needExpandSize -= (m_size - usedLen);
	}
	auto newData = new char[m_size];
	if (m_write < m_read)
	{
		unsigned int write = m_write;
		m_write += (m_size - size);
		memcpy(newData, m_data, size);
		for (int i = 0; i <= write; ++i)
		{
			newData[size + i] = newData[i];
		}
	}
	else
	{
		memcpy(newData, m_data, size);
	}
	delete[] m_data;
	m_data = newData;
}

void RingBuffer::shrinkSize()
{
	unsigned int curUsedLen = getUsedLen();
	int leftUsedLen = curUsedLen;
	while (leftUsedLen > 0 && m_size / 2 > leftUsedLen)
	{
		m_size /= 2;
		leftUsedLen -= m_size;
	}
	if (leftUsedLen == curUsedLen) return;

	auto newData = new char[m_size];
	if (m_write > m_read)
	{
		memcpy(newData, m_data, curUsedLen);
		m_write -= m_read;
	}
	else
	{
		m_write = m_write % m_size;
		unsigned int unReadLen = m_size - m_read % m_size;
		memcpy(newData, m_data, unReadLen);
		memcpy(newData + unReadLen, m_data, m_write);
		m_read = m_write + 1;
	}
	m_read = 0;
	delete[] m_data;
	m_data = newData;
	std::cout << "shrinkSize" << m_size << std::endl;
}

void RingBuffer::printAll()
{
	std::cout << std::endl;
	std::cout << "read is" << m_read << " write is " << m_write << " UsedLen is " << getUsedLen() << " size is " << m_size << std::endl;
	if (isEmpty())	return;

	if (m_write > m_read)
	{
		for (int i = m_read; i < m_write; ++i) {
			std::cout << m_data[i];
		}
	}
	else
	{
		for (int i = m_read; i < m_size; ++i) {
			std::cout << m_data[i];
		}
		for (int i = 0; i < m_write; ++i) {
			std::cout << m_data[i];
		}
	}
	std::cout << std::endl;
}