//#include"ThreadPool.h"
//using namespace threadpool;
//
//int main(void)
//{
//	ThreadPool::instance()->initialize(20,10);
//	::Sleep(500);
//	ThreadPool::instance()->set_thread_count(15);
//	ThreadPool::instance()->shutdown(); 
//	ThreadPool::instance()->destroy_instance();
//
//	return 0;
//
//}

#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>
#include<thread>
#include"networking.hpp"
#include "ThreadPool.h"
int main(void)
{
	//step 0:初始化Winsock库
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock_listen = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen == INVALID_SOCKET)
		return -1;

	//step 2:bind to a local address and port
	//fill out the structure of address
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = (htons(2049));
	local_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.9");
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
	threadpool::ThreadPool::instance()->initialize(20, 10);
	while (true)
	{
		SOCKET sock_work = ::accept(sock_listen,
			reinterpret_cast<struct sockaddr*>(&client_addr),
			&len);
		if (sock_work == SOCKET_ERROR)
			continue;


		std::thread t1([sock_work](void) mutable->void {

			//step 5:send and receive data from client  
			int sent_num = ::send(sock_work,
				reinterpret_cast<const char*>(L"Welcome"),
				wcslen(L"Welcome") * 2,
				0);

			wchar_t buf[50] = { 0 };
			int recv_num = ::recv(sock_work, reinterpret_cast<char*>(&buf), 50, 0);
			if (recv_num > 0)
				std::wcout << buf << std::endl;

			::closesocket(sock_work);
			//start a new thread
			threadpool::ThreadPool::instance()->add_task(new net_work_task(sock_work));
			threadpool::ThreadPool::instance()->shutdown();
			threadpool::ThreadPool::instance()->destroy_instance();

		});
		t1.detach();
	}


	//step 6: close the socket

	::closesocket(sock_listen);
	::WSACleanup();     //终止使用Winsock 2 DLL

	return 0;
};