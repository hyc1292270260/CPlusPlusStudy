#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>



int main(void)
{
	//step 0:≥ı ºªØWinsockø‚
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		return -1;

	//step 2: send and receive data
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = (htons(2019));
	server_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.5");
	wchar_t buf[50] = { 0 };
	int len = sizeof(server_addr);
	
	
	::sendto(sock,
		reinterpret_cast<const char*>(L"client received"),
		sizeof(L"client received"),
		0,
		reinterpret_cast<sockaddr*>(&server_addr),
		len);
	int recv_num = ::recvfrom(sock,
		reinterpret_cast<char*>(buf),
		50,
		0,
		reinterpret_cast<sockaddr*>(&server_addr),
		&len);
	if (recv_num > 0)
		std::wcout << buf << std::endl;


	//step 3: close the socket
	::closesocket(sock);
	::WSACleanup();
	return 0;
}