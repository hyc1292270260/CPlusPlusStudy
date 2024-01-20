#include "SocketClient.h"
#include <iostream>
#include <thread>

void SocketClient::init()
{
	//	init Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return;
}

void SocketClient::send()
{
	// create a socket
	SOCKET socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (socket == INVALID_SOCKET)
	{
		cleanUp(socket);
		return;
	}

	// connect with server
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = (htons(2049));
	server_addr.sin_addr.S_un.S_addr = ::inet_addr("10.89.136.61");
	int result = ::connect(socket,
		reinterpret_cast<const struct sockaddr*>(&server_addr),
		sizeof(server_addr));

	if (result == SOCKET_ERROR)
	{
		cleanUp(socket);
		return;
	}

	// send and receive data from server in new thread
	std::thread t([socket, this]()->void {
		wchar_t buf[50]{ 0 };
		int recv_num = ::recv(socket, reinterpret_cast<char*>(&buf), 50, 0);
		if (recv_num > 0)
			std::wcout << "client recv: " << buf << std::endl;
		std::wcin >> buf;
		::send(socket,
			reinterpret_cast<const char*>(buf),
			wcslen(buf) * 2,
			0);
	});

	t.join();
	cleanUp(socket);
}


void SocketClient::cleanUp(SOCKET& socket)
{
	::closesocket(socket);
	::WSACleanup();
}
