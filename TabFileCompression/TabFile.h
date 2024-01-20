#pragma once
#include <string>
#include <vector>
#include <map>
#include "BitOperationHelper.hpp"

using namespace std;


#define DEFAULT_INT 0
#define DEFAULT_STRING ""

enum EFieldType
{
	EF_INT = 0,
	EF_STRING
};

struct TabDataField
{

public:
	TabDataField(string key, int offSet, EFieldType fieldType) :Key(key), Offset(offSet), FieldType(fieldType) {}
	string Key;
	int Offset;
	EFieldType FieldType;
};

template<typename T>
static T& TabFileGetFieldByOffset(void* data, unsigned int offset)
{
	return *(T*)((char*)data + offset);
}


class TabFile
{
public:

	TabFile() { };
	virtual ~TabFile()
	{
		FieldMap.clear();
		FieldKey.clear();
	};
	virtual void RegisterParams() {};
	virtual int& GetKey() = 0;
	virtual int GetKeySize() { return sizeof(int); };
	void RegisterField(const string& key, int offset, int field);
	void RegisterField(const string& key, int offset, const string& field);
	int Load(const vector<string>& columnNames, const vector<string>& columnDatas);
	void LoadFromBuffer(char* buffer, int bitPos);
	void WriteToBuffer(char* buffer, int& bitBodyPos);


protected:
	map<string, TabDataField> FieldMap;
	vector<string> FieldKey;
	int Size;
};