#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>
#include<thread>
#include<fstream>
#include<mutex>
#include"File_Server.h"
constexpr unsigned int BUF_SIZE = 1024 * 256;


int wmain(int ac,wchar_t* av[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock_listen = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen == INVALID_SOCKET)
		return -1;

	//step 2:bind to a local addtress and port
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = (htons(2049));
	local_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.106");
	int result = ::bind(sock_listen,
		reinterpret_cast<const struct sockaddr*>(&local_addr),
		sizeof(local_addr));

	if (result == SOCKET_ERROR)
		return -1;


	//step 3:listen
	result = ::listen(sock_listen, 1 /*SOMAXCONN*/);
	if (result == SOCKET_ERROR)
		return -1;

	//step 4:accept(maybe block)
	struct sockaddr_in client_addr = { 0 };
	int len = sizeof(client_addr);
	while (true)
	{
		SOCKET sock_work = ::accept(sock_listen,
			reinterpret_cast<struct sockaddr*>(&client_addr),
			&len);
		if (sock_work == SOCKET_ERROR)
			continue;
		

		const char* ip = inet_ntoa(client_addr.sin_addr);
		if (ip)
			std::cout << ip << std::endl;
		std::thread t0([sock_work,av](void) mutable->void {
			//open a file
			std::fstream fs;
			fs.open(av[1], std::ios_base::in | std::ios_base::binary);

			if (!fs)
				return;
			//move to the end of file for calculate size
			fs.seekg(0, std::ios_base::end);
			unsigned long long int size =fs.tellg();
			fs.seekg(0,std::ios_base::beg);

			//prepare the file header
			FileHeader fileHeader;
			fileHeader.file_size = size;

			//send the header
			int sent = ::send(sock_work,
				reinterpret_cast<const char*>(&fileHeader),
				sizeof(fileHeader),
				0);
			if (sent != sizeof(fileHeader))
			{
				fs.close();
				::closesocket(sock_work);
				sock_work = INVALID_SOCKET;
				return;
			}
			char* buf = new char[BUF_SIZE];
	
			while (!fs.eof())
			{
				fs.read(buf,BUF_SIZE);
				int read_size = fs.gcount();
				int sent = ::send(sock_work,
					 buf,
					 read_size,
					 0);

				if (sent != read_size)
					break;							
			}

			delete[] buf;
			buf = nullptr;
			fs.close();
			::closesocket(sock_work);
			sock_work = INVALID_SOCKET;
			
		});
		t0.detach();
	}
	::WSACleanup();
	return 0;
}