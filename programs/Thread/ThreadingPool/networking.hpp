#include"ITask.h"
#include"windows.h"
#include<iostream>

class net_work_task :public threadpool::Itask
{
public:
	net_work_task(SOCKET sock):_sock(sock)
	{
	}
	virtual void run(void)
	{
		if (_sock==INVALID_SOCKET)
			return;
		//step 5:send and receive data from client  
		int sent_num = ::send(_sock,
			reinterpret_cast<const char*>(L"Welcome"),
			wcslen(L"Welcome") * 2,
			0);

		wchar_t buf[50] = { 0 };
		int recv_num = ::recv(_sock, reinterpret_cast<char*>(&buf), 50, 0);
		if (recv_num > 0)
			std::wcout << buf << std::endl;

		::closesocket(_sock);
	}
private:
	SOCKET _sock;
};