#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <map>
#include <filesystem>
#include <string_view>
#include <WinSock2.h>
#include <memory>
#include "FileHeader.h"

#pragma comment(lib, "WS2_32.lib")
constexpr unsigned BUF_SIZE = 1024 * 512;
std::map<unsigned long long, std::wstring> library;

void transfer_meta(wchar_t** av, FileHeader fileHeader, SOCKET server_sock);

int wmain(int ac, wchar_t* av[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		return -1;
	struct sockaddr_in listen_addr = { 0 };
	listen_addr.sin_addr.S_un.S_addr = inet_addr("192.168.31.18");
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(2019);
	int result = bind(
		listen_sock,
		reinterpret_cast<struct sockaddr*>(&listen_addr),
		sizeof listen_addr);
	if (result == SOCKET_ERROR)
		return -1;

	result = listen(listen_sock, SOMAXCONN);
	if (result == SOCKET_ERROR)
		return -1;

	struct sockaddr_in client_addr = { 0 };
	int length = sizeof client_addr;

	while (true)
	{
		SOCKET server_sock = accept(
			listen_sock,
			reinterpret_cast<struct sockaddr*>(&client_addr),
			&length);
		if (server_sock == INVALID_SOCKET)
			continue;
		std::thread td([=](void)mutable -> void
			{
				FileHeader fileHeader;
				result = recv(
					server_sock,
					reinterpret_cast<char*>(&fileHeader),
					sizeof fileHeader,
					0);
				if (result != sizeof fileHeader)
				{
					closesocket(server_sock);
					return;
				}
				if (fileHeader.fileID == 0)
					transfer_meta(av, fileHeader, server_sock);

				// result = listen(listen_sock, SOMAXCONN);
				else if (fileHeader.fileID != 0)
				{
					auto it = library.find(fileHeader.fileID);
					if (it == library.end())
					{
						closesocket(server_sock);
						return;
					}
					std::fstream fs;

					fs.open(it->second, fs.in | fs.binary);
					if (!fs)
					{
						closesocket(server_sock);
						return;
					}
					char* buffer1 = new char[BUF_SIZE];
					char* buffer2 = new char[BUF_SIZE];
					unsigned sending_size = BUF_SIZE;
					int buffer_number = 1;
					int transfer_size;
					bool finished = false;

					std::mutex mx;
					std::condition_variable cv;

					std::thread td1([&, buffer1, buffer2](void) mutable -> void
						{
							int size;
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							while (!fs.eof() && !finished)
							{
								fs.read(buffer_number == 1 ? buffer1 : buffer2, BUF_SIZE);
								size = fs.gcount();
								std::unique_lock<std::mutex> lck(mx);
								transfer_size = size;
								buffer_number == 1 ? 2 : 1;
								cv.notify_one();
							}
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							std::unique_lock<std::mutex> lck(mx);
							finished = true;
							cv.notify_one();
						});
					std::thread td2([&, buffer1, buffer2](void) mutable -> void
						{
							std::unique_lock<std::mutex> lck(mx);
							while (!finished)
							{
								cv.wait(lck);
								if (finished)
									return;
								result = send(
									server_sock,
									buffer_number == 1 ? buffer1 : buffer2,
									transfer_size,
									0);
								if (result != transfer_size)
									finished = true;
							}
						});
					td1.join();
					td2.join();

					delete[] buffer1;
					delete[] buffer2;
					
				}
			});
		td.detach();
		/*if (server_sock != INVALID_SOCKET)
			closesocket(server_sock);*/
	}

	closesocket(listen_sock);
	WSACleanup();

	return 0;
}

void transfer_meta(wchar_t** av, FileHeader fileHeader, SOCKET server_sock)
{
	std::filesystem::path path(av[1]);
	auto filename = path.filename();
	int offset = path.wstring().length() - filename.wstring().length();
	unsigned long long fileID = 1;

	wcscpy(fileHeader.path, filename.wstring().c_str());
	fileHeader.fileType = FileType::directory;
	fileHeader.fileSize = 0;
	fileHeader.fileID = fileID++;

	int result = send(
		server_sock,
		reinterpret_cast<const char*>(&fileHeader),
		sizeof fileHeader,
		0);
	if (result != sizeof fileHeader)
	{
		closesocket(server_sock);
		return;
	}
	library[fileHeader.fileID] = path.generic_wstring();

	for (auto& p : std::filesystem::recursive_directory_iterator(av[1]))
	{
		auto sub_path = p.path().wstring();
		if (p.is_directory() || p.is_regular_file())
		{
			fileHeader.fileID = fileID;
			library[fileID++] = sub_path;
		}
		else
			continue;

		std::wstring_view sv = sub_path;
		sv.remove_prefix(offset);
		wcscpy(fileHeader.path, sv.data());
		if (p.is_directory())
		{
			fileHeader.fileType = FileType::directory;
			fileHeader.fileSize = 0;
		}
		else if (p.is_regular_file())
		{
			fileHeader.fileType = FileType::file;
			fileHeader.fileSize = p.file_size();
		}

		int sent = send(
			server_sock,
			reinterpret_cast<const char*>(&fileHeader),
			sizeof fileHeader,
			0);
		if (sent != sizeof fileHeader)
		{
			closesocket(server_sock);
			return;
		}
	}
	fileHeader.fileType = FileType::finish;
	result = send(
		server_sock,
		reinterpret_cast<const char*>(&fileHeader),
		sizeof fileHeader,
		0);
	if (result != sizeof fileHeader)
	{
		closesocket(server_sock);
		return;
	}
	closesocket(server_sock);
}