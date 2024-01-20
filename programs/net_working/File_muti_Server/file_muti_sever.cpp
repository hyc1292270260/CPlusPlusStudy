#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include<cstring>
#include<iostream>
#include<thread>
#include<fstream>
#include<mutex>
#include<chrono>
#include<windows.h>

#include"..//File-Server/File_Server.h"
constexpr unsigned int BUF_SIZE = 1024 * 256;


int wmain(int ac, wchar_t* av[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;

	//step 1:create a socket
	SOCKET sock_listen = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen == INVALID_SOCKET)
		return -1;

	//step 2:bind to a local address and port
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = (htons(2049));
	local_addr.sin_addr.S_un.S_addr = ::inet_addr("192.168.0.17");
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
		std::thread t0([sock_work, av](void) mutable->void {
			//open a file
			std::fstream fs;
			fs.open(av[1], std::ios_base::in | std::ios_base::binary);

			if (!fs)
				return;
			//move to the end of file
			fs.seekg(0, std::ios_base::end);
			unsigned long long int size = fs.tellg();
			fs.seekg(0, std::ios_base::beg);

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
		
			//send the file
			char* buf1 = new char[BUF_SIZE];
			char* buf2 = new char[BUF_SIZE];
			int cur_resume_length = 0;
			int cur_resume_buf = 1;
			bool b_exit = false;
			std::mutex mx;
			std::condition_variable cv;
			//HANDLE hevent = ::CreateEvent(nullptr,false,true,nullptr);
			//HANDLE hexit = ::CreateEvent(nullptr, false, false, nullptr);

			//create stage1
			std::thread s1(
				[&cv,&mx,&fs,&b_exit,&cur_resume_buf,&cur_resume_length,buf1,buf2](void)mutable->void {

				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				while (!fs.eof() && !b_exit)
				{
					fs.read(cur_resume_buf == 1 ? buf2 : buf1,BUF_SIZE);
					int size_read = fs.gcount();
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					std::unique_lock<std::mutex> lck(mx);				
					cur_resume_buf = cur_resume_buf == 1 ? 2 : 1;   //exchange buffer
					cur_resume_length = size_read;
					
					cv.notify_one();					//inform  stage2
				} 
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				std::unique_lock<std::mutex> lck(mx);				
				b_exit = true;
				cv.notify_one(); 
				
			});

			//create stage2
			std::thread s2(
				[sock_work,&cv,&b_exit, &mx, &fs, &cur_resume_buf, &cur_resume_length, buf1, buf2](void)mutable->void {
								
				std::unique_lock<std::mutex> lck(mx);			//确保send为原子操作
				while (!b_exit)
				{					
					cv.wait(lck);     //wait 时才会释放锁
					if (b_exit)
						break;
					int sent = ::send(sock_work,
						cur_resume_buf == 1 ? buf1 : buf2,
						cur_resume_length,
						0);

					if (sent != cur_resume_length)
					{
						b_exit = true;
						break;
					}
					
				}
			});
			
			s1.join();
			s2.join();
			delete[] buf1;
			buf1 = nullptr;
			delete[] buf2;
			buf2 = nullptr;

			fs.close();
			::closesocket(sock_work);
			sock_work = INVALID_SOCKET;
			/*::CloseHandle(hevent);
			hevent = nullptr;
			::CloseHandle(hexit);
			hexit = nullptr;*/

		});
		t0.detach();
	}
	::WSACleanup();
	return 0;
}