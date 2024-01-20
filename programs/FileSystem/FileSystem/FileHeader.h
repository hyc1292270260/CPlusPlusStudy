#pragma once

// file type;
enum class FileType
{
	file = 0,
	directory,
	finish
};

// POD class.
class FileHeader
{
public:
	FileType fileType;
	wchar_t path[255];
	unsigned long long fileSize;
	unsigned long long fileID;

};