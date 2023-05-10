#pragma once
#include <string>
#include "TabFile.h"
#include "CompressTabFile.hpp"
class TabFileCustom : public TabFile
{
public:
	int Id;
	std::string Name;
	std::string Desc;
	int Num;
	TabFileCustom()
		: Id(-1)
	{}

	virtual int& GetKey() override
	{
		return Id;
	}

	virtual void RegisterParams() override
	{
		RegisterField("id", offsetof(TabFileCustom, Id), Id);
		RegisterField("name", offsetof(TabFileCustom, Name), Name);
		RegisterField("desc", offsetof(TabFileCustom, Desc), Desc);
		RegisterField("num", offsetof(TabFileCustom, Num), Num);
	}
};

class TabFileCustomCompress : public CompressTabFile<int, TabFileCustom>
{
};