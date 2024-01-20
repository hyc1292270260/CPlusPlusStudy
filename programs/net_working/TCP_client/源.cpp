#include<Winsock2.h>
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
	SOCKET sock_connect = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_connect == INVALID_SOCKET)
		return -1;

	//step2:connect with server
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = (htons(2049));
	server_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.107");
	int result = ::connect(sock_connect,
		reinterpret_cast<const struct sockaddr*>(&server_addr),
		sizeof(server_addr));

	if (result == SOCKET_ERROR)
		return -1;

	//step3:sending and receiving data from server
	wchar_t buf[50] = { 0 };
	int recv_num = ::recv(sock_connect, reinterpret_cast<char*>(&buf), 50, 0);
	if (recv_num > 0)
		std::wcout << buf << std::endl;
	std::wcin >> buf;
	::send(sock_connect,
		reinterpret_cast<const char*>(buf),
		wcslen(buf) * 2,
		0);
	//step4:close the socket
	::closesocket(sock_connect);
	::WSACleanup();     

	return 0;
}