#include "../FileSystem/FileHeader.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <WinSock2.h>
#include <list>
#include <cstring>
#pragma comment(lib, "WS2_32.lib")

constexpr unsigned BUF_SIZE = 1024 * 1024 * 2;
std::list<FileHeader>* filetable = new std::list<FileHeader>;

void fill_list(SOCKET client_sock);

int wmain(int ac, wchar_t* av[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == INVALID_SOCKET)
		return -1;
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.31.18");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2019);

	int result = connect(
		client_sock,
		reinterpret_cast<struct sockaddr*>(&server_addr),
		sizeof server_addr);
	if (result == SOCKET_ERROR)
		return -1;


	FileHeader request;
	request.fileID = 0;

	result = send(
		client_sock,
		reinterpret_cast<const char*>(&request),
		sizeof(request),
		0);
	if (result != sizeof(request))
		return -1;

	fill_list(client_sock);
	closesocket(client_sock);
	client_sock = INVALID_SOCKET;

	unsigned long long remained_file_size = 0;
	unsigned buf_remained;
	char* buffer = new char[BUF_SIZE];

	for (std::list<FileHeader>::iterator it = filetable->begin(); it != filetable->end(); ++it)
	{	
		request = *it;
		std::wstring filename(av[1]);
		if (request.fileType == FileType::directory)
		{
			std::filesystem::path directory_path(filename + request.path);
			if (CreateDirectoryW(directory_path.wstring().c_str(), NULL))
				continue;
			else
				return -1;
		}
		else if (request.fileType == FileType::file)
		{
			client_sock = socket(AF_INET, SOCK_STREAM, 0);
			remained_file_size = request.fileSize;

			result = connect(
				client_sock,
				reinterpret_cast<struct sockaddr*>(&server_addr),
				sizeof server_addr);
			if (result == SOCKET_ERROR)
				return -1;

			result = send(
				client_sock,
				reinterpret_cast<const char*>(&request),
				sizeof(request),
				0);
			if (result != sizeof(request))
			{
				closesocket(client_sock);
				return -1;
			}

			std::fstream fs;
			fs.open(filename + request.path, fs.out | fs.binary | fs.trunc);
			if (!fs)
			{
				closesocket(client_sock);
				return -1;
			}

			while (remained_file_size > 0)
			{
				buf_remained = remained_file_size < BUF_SIZE ? remained_file_size : BUF_SIZE;
				unsigned offset = 0;
				while (buf_remained > 0)
				{
					result = recv(
						client_sock,
						buffer + offset,
						buf_remained,
						0);
					if (result <= 0)
						break;

					buf_remained -= result;
					offset += result;
				}
				fs.write(buffer, offset);
				remained_file_size -= offset;
			}
			closesocket(client_sock);
			client_sock = INVALID_SOCKET;
		}
	}

	WSACleanup();
	delete[] buffer;
	filetable->clear();

	return 0;
}

void fill_list(SOCKET client_sock)
{
	while (true)
	{
		FileHeader request;
		int fileHeader_total_size = sizeof request;
		int fileHeader_remained = fileHeader_total_size;
		int result;
		while (fileHeader_remained > 0)
		{
			result = recv(
				client_sock,
				reinterpret_cast<char*>(&request) + (fileHeader_total_size - fileHeader_remained),
				fileHeader_remained,
				0);
			if (result != sizeof(request))
			{
				closesocket(client_sock);
				return;
			}
			fileHeader_remained -= result;
		}

		if (request.fileType == FileType::finish)
			break;
		else if (request.fileType == FileType::directory || request.fileType == FileType::file)
			filetable->emplace_back(request);
	}
}