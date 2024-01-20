#include "SocketServer.h"
#include <iostream>
#include <thread>

void SocketServer::init()
{
	//	init Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return;
}

void SocketServer::send()
{
	// create a socket
	SOCKET socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (socket == INVALID_SOCKET)
	{
		cleanUp(socket);
		return;
	}

	//step 2:bind to a local address and port
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = (htons(2049));
	local_addr.sin_addr.S_un.S_addr = ::inet_addr("10.89.136.61");
	int result = ::bind(socket,
		reinterpret_cast<const struct sockaddr*>(&local_addr),
		sizeof(local_addr));

	if (result == SOCKET_ERROR)
	{
		cleanUp(socket);
		return;
	}

	// listen
	result = ::listen(socket, 1);
	if (result == SOCKET_ERROR)
	{
		cleanUp(socket);
		return;
	}

	//step 4:accept(maybe block)
	struct sockaddr_in client_addr = { 0 };
	int len = sizeof(client_addr);
	while (true)
	{
		SOCKET sock_work = ::accept(socket,
			reinterpret_cast<struct sockaddr*>(&client_addr),
			&len);
		if (sock_work == SOCKET_ERROR)
			continue;
		std::thread t([sock_work]() ->void {

			// send and receive data from client  
			int sent_num = ::send(sock_work,
				reinterpret_cast<const char*>(L"Welcome"),
				wcslen(L"Welcome") * 2,
				0);

			wchar_t buf[50] = { 0 };
			int recv_num = ::recv(sock_work, reinterpret_cast<char*>(&buf), 50, 0);
			if (recv_num > 0)
				std::wcout << "server recv: " << buf << std::endl;
		});
		t.join();
	}
	cleanUp(socket);
}


void SocketServer::cleanUp(SOCKET& socket)
{
	::closesocket(socket);
	::WSACleanup();
}
