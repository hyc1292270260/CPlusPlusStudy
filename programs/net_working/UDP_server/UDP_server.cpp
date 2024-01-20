#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>
#include<ws2ipdef.h>


int main(void)
{
	//step 0:初始化Winsock库
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		return -1;

	////广播
	//bool b_enable = true;
	//int result = ::setsockopt(
	//	sock,
	//	SOL_SOCKET,
	//	SO_BROADCAST,
	//	reinterpret_cast<const char*>(&b_enable),
	//	sizeof(b_enable));

	//if (result == SOCKET_ERROR)
	//	return -1;

	//step 2:bind to a local addtress and port
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = (htons(2019));
	local_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.5");
	int result = ::bind(sock,
		reinterpret_cast<const struct sockaddr*>(&local_addr),
		sizeof(local_addr));

	if (result == SOCKET_ERROR)
		return -1;

	/*bool bEnable = false;
	if (::setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char*>(&bEnable), sizeof true) != 0)
		return -1;*/
	

	//组播
	IP_MREQ mq;
	mq.imr_interface.S_un.S_addr = ::inet_addr("192.168.0.5");
	mq.imr_multiaddr.S_un.S_addr = ::inet_addr("224.0.0.2");     //组播地址
	result = ::setsockopt(
		sock,
		IPPROTO_IP,
		IP_ADD_MEMBERSHIP,
		reinterpret_cast<const char*>(&mq),
		sizeof mq);

	if (result == SOCKET_ERROR)
		return -1;




	//step 3:sbend and receive data from client 

	wchar_t buf[50] = { 0 };
	struct sockaddr_in client_addr = { 0 };
	int len = sizeof(client_addr);

	//first receive,don't know the addtress of client

	int recv_num = ::recvfrom(sock,
		reinterpret_cast<char*>(buf),
		50,
		0,
		reinterpret_cast<sockaddr*>(&client_addr),
		&len);
	if(recv_num >0)
		std::wcout << buf << std::endl;

	::sendto(sock,
		reinterpret_cast<const char*>(L"Welcome"),
		wcslen(L"Welcome") * 2,
		0,
		reinterpret_cast<sockaddr*>(&client_addr),
		len);

	//step 4: close the socket
	::closesocket(sock);
	::WSACleanup();
	return 0;
}