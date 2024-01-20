// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;
#define Define_Size 1024
const char* SEPARATOR = "\t";
template<typename TabDataKeyType, typename TabData>
class CompressTabFile
{
public:
	CompressTabFile()
	{
	}

	virtual ~CompressTabFile()
	{
		if (Buffer)
		{
			free(Buffer);
			Buffer = nullptr;
		}
	}

	void ResetBufferSize(int size)
	{
		if (!Buffer)
		{
			Buffer = (char*)malloc(size);
			BufferSize = size;
			memset(Buffer, 0, BufferSize);
		}
		else
		{
			char* p = (char*)realloc(Buffer, size);
			assert(p);
			Buffer = p;
			BufferSize = size;
		}
	}

	int GetKey(int key)
	{
		return key;
	}

	int GetKey(const string& key)
	{
		return GetHash(key);
	}

	int GetKeySize()
	{
		return sizeof(int);
	}

	int GetHash(const string& key)
	{
		int hash = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hash = key[i] + 65599 * hash;
		}
		// 低31位保证非负整数
		return (hash & 0x7FFFFFFF);
	}

	void ParseInToArray(const string& srcString, vector<string>& outArray, const char* separator)
	{
		outArray.clear();
		int seqLen = strlen(separator);
		int strLen = srcString.length();
		if (strLen > 0 && seqLen > 0)
		{
			int findIndex = 0;
			int pos = srcString.find(separator, findIndex);
			while (pos >= 0)
			{
				outArray.push_back(srcString.substr(findIndex, pos - findIndex));
				findIndex = pos + seqLen;
				pos = srcString.find(separator, findIndex);
			}
			outArray.push_back(srcString.substr(findIndex, strLen - findIndex));
		}
	}

	virtual bool Load(const string& name)
	{
		ifstream tabFileStream(name);
		if (!tabFileStream)
			return false;

		string lineStr;
		getline(tabFileStream, lineStr);
		vector<string> columns;
		ParseInToArray(lineStr, columns, SEPARATOR);

		int size = 0;
		vector<TabData*> tabData;
		vector<string> lineData;
		while (getline(tabFileStream, lineStr))
		{
			ParseInToArray(lineStr, lineData, SEPARATOR);
			TabData* data = new TabData();
			data->RegisterParams();
			size += data->Load(columns, lineData);
			tabData.push_back(data);
		}
		if (tabData.size() == 0)
		{
			tabFileStream.close();
			return false;
		}
		ResetBufferSize(size + sizeof(int));

		int headBitPos = 0;
		int dataCount = tabData.size();
		BitOperations::WriteDataToBuffer((Byte*)Buffer, dataCount, headBitPos);
		int bitBodyPos = GetKeySize() + dataCount * 8;
		for (int i = 0; i < tabData.size(); i++)
		{
			// write head
			// write key
			int key = GetKey(tabData[i]->GetKey());
			BitOperations::WriteDataToBuffer((Byte*)Buffer, key, headBitPos);
			// write bit offset
			BitOperations::WriteDataToBuffer((Byte*)Buffer, bitBodyPos, headBitPos);

			// write body
			tabData[i]->WriteToBuffer(Buffer, bitBodyPos);
		}

		for (int i = tabData.size() - 1; i >= 0; i--)
		{
			delete tabData[i];
		}
		tabData.clear();
		ResetBufferSize(ceil(bitBodyPos / 8));
		tabFileStream.close();
		return true;
	}

	virtual bool Find(TabDataKeyType key, TabData& data)
	{
		int count = 0;
		int intSize = sizeof(int);
		memcpy(&count, Buffer, intSize);

		int dataBitOffset = -1;
		int pos = intSize;
		int intKey = GetKey(key);
		for (int i = 0; i < count; i++)
		{
			int dataKey = 0;
			memcpy(&dataKey, Buffer + pos, intSize);
			pos += intSize;
			if (dataKey != intKey)
			{
				pos += intSize;
				continue;
			}
			memcpy(&dataBitOffset, Buffer + pos, intSize);
			break;
		}

		if (dataBitOffset < 0)
			return false;

		data.LoadFromBuffer(Buffer, dataBitOffset);
		return true;
	}

protected:
	char* Buffer;
	int BufferSize;
};