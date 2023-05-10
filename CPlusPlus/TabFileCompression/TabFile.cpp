#include "TabFile.h"

void TabFile::RegisterField(const string& key, int offset, int field)
{
	TabDataField fieldData(key, offset, EFieldType::EF_INT);
	FieldMap.insert(make_pair(key, fieldData));
	FieldKey.push_back(key);
}

void TabFile::RegisterField(const string& key, int offset, const string& field)
{
	TabDataField fieldData(key, offset, EFieldType::EF_STRING);
	FieldMap.insert(make_pair(key, fieldData));
	FieldKey.push_back(key);
}

int TabFile::Load(const vector<string>& columnNames, const vector<string>& columnDatas)
{
	for (int i = 0; i < columnNames.size(); i++)
	{
		auto it = FieldMap.find(columnNames[i]);
		if (it != FieldMap.end())
		{
			string data = columnDatas[i];
			TabDataField field = it->second;
			switch (field.FieldType)
			{
			case EFieldType::EF_STRING:
			{
				string tempStr = DEFAULT_STRING;
				if (data.length() > 0 && data.compare(DEFAULT_STRING) != 0)
				{
					tempStr = data;
				}
				TabFileGetFieldByOffset<string>(this, field.Offset) = tempStr;
				Size += tempStr.size();
			}
			break;
			case EFieldType::EF_INT:
			{
				int tempInt = DEFAULT_INT;
				if (data.length() > 0)
				{
					tempInt = stoi(data);
				}
				TabFileGetFieldByOffset<int>(this, field.Offset) = tempInt;
				Size += sizeof(int);
			}
			break;
		defalut:
			assert("TabFile->Load: Unsupported type!!!");
			}

		}
	}
	Size += columnNames.size() * sizeof(int);
	return Size;
}

void TabFile::LoadFromBuffer(char* buffer, int bitPos)
{
	for (int i = 0; i < FieldKey.size(); i++)
	{
		string key = FieldKey[i];
		auto it = FieldMap.find(FieldKey[i]);
		assert(it != FieldMap.end());

		auto field = it->second;
		int bitValue;
		BitOperations::ReadOneBit((Byte*)(buffer), bitPos++, bitValue);
		switch (field.FieldType)
		{
		case EFieldType::EF_STRING:
		{
			string& temp = TabFileGetFieldByOffset<string>(this, field.Offset);
			if (bitValue > 0)
			{
				temp = "";
				while (true)
				{
					char CharTemp = 0;
					BitOperations::ReadDataFromBuffer((Byte*)(buffer), CharTemp, bitPos);
					bitPos += sizeof(char) * 8;
					temp.push_back(CharTemp);
					if (CharTemp == 0)
					{
						break;
					}
				}
			}
			else
			{
				temp = DEFAULT_STRING;
			}
		}
		break;
		case EFieldType::EF_INT:
		{
			int& temp = TabFileGetFieldByOffset<int>(this, field.Offset);
			if (bitValue > 0)
			{
				int value = 0;
				BitOperations::ReadDataFromBuffer((Byte*)(buffer), value, bitPos);
				bitPos += sizeof(int) * 8;
				temp = value;
			}
			else
			{
				temp = DEFAULT_INT;
			}
		}
		default:
			assert("TabFile->LoadFromBuffer: Unsupported type!!!");
		}
	}

}

void TabFile::WriteToBuffer(char* buffer, int& bitBodyPos)
{
	char* bodyBuffer = buffer + bitBodyPos;
	for (int i = 0; i < FieldKey.size(); i++)
	{
		string Key = FieldKey[i];
		auto it = FieldMap.find(FieldKey[i]);
		assert(it != FieldMap.end());

		auto field = it->second;
		switch (field.FieldType)
		{
		case EFieldType::EF_STRING:
		{
			string temp = TabFileGetFieldByOffset<string>(this, field.Offset);
			if (temp.compare(DEFAULT_STRING) != 0)
			{
				BitOperations::WriteOneBit((Byte*)buffer, 1, bitBodyPos);
				int Index = 0;
				while (Index < temp.length())
				{
					BitOperations::WriteDataToBuffer((Byte*)buffer, temp.at(Index), bitBodyPos);
					Index++;
				}
				BitOperations::WriteOneBit((Byte*)buffer, 0, bitBodyPos);
			}
			else
			{
				BitOperations::WriteOneBit((Byte*)buffer, 0, bitBodyPos);
			}
		}
		break;
		case EFieldType::EF_INT:
		{
			int temp = TabFileGetFieldByOffset<int>(this, field.Offset);
			if (temp != DEFAULT_INT)
			{
				BitOperations::WriteOneBit((Byte*)buffer, 1, bitBodyPos);
				BitOperations::WriteDataToBuffer((Byte*)buffer, temp, bitBodyPos);
			}
			else
			{
				BitOperations::WriteOneBit((Byte*)buffer, 0, bitBodyPos);
			}
		}
		break;
		default:
			assert("TabFile->LoadFromBuffer: Unsupported type!!!");
		}

	}
}