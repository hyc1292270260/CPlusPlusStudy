#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>
#include"..//File-Server/File_Server.h"
#include<fstream>

constexpr unsigned int RECV_BUF_SIZE = 1024 * 1024 *4 ;
int wmain(int ac, wchar_t* av[] )
{
	//step 0:初始化Winsock库
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock_connect = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_connect == INVALID_SOCKET)
		return -1;

	//step2:connect with server
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = (htons(2049));
	server_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.17");
	int result = ::connect(sock_connect,
		reinterpret_cast<const struct sockaddr*>(&server_addr),
		sizeof(server_addr));

	if (result == SOCKET_ERROR)
		return -1;


	
	std::fstream fs;
	char* buf = new char[RECV_BUF_SIZE];
	unsigned long long int cur_total_remainder = 0ull;
	unsigned long long int cur_should_recv = 0ull;
	unsigned long long int cur_had_recv = 0ull;

	//receive the file header
	FileHeader fileHeader;
	int recv = ::recv(sock_connect, 
		reinterpret_cast<char*>(&fileHeader),
		sizeof(fileHeader),
		0);
	
	if (recv != sizeof(fileHeader))
		goto _target;

	cur_total_remainder = fileHeader.file_size;
	//open the written file
	fs.open(av[1], std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if(!fs)
		goto _target;

	//received the file
	while (cur_total_remainder > 0)           //每次接受cur_should_recv
	{
		cur_should_recv = cur_total_remainder > RECV_BUF_SIZE ? RECV_BUF_SIZE : cur_total_remainder;
		cur_had_recv = 0ull;
		while (cur_should_recv > 0)   
		{
			int recv = ::recv(sock_connect,  //受网络等限制，不一定传多少
				buf + cur_had_recv,
				cur_should_recv,
				0);

			if (recv < 0)
				goto _target;

			cur_should_recv -= recv;
			cur_had_recv += recv;
		}
		fs.write(buf, cur_had_recv);
		cur_total_remainder -= cur_had_recv;
	}
	
_target:
	if (buf)
	{
		delete[] buf;
		buf = nullptr;
	}
	fs.close();
	::closesocket(sock_connect);
	sock_connect = INVALID_SOCKET;

	::WSACleanup();
	return 0;
}