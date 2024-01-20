#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hMutex = nullptr;
HANDLE hEvent = nullptr;
CRITICAL_SECTION cs;  //用户区，速度快
int tickets = 100;
unsigned long WINAPI Terminal1(void* lpParameter);
unsigned long WINAPI Terminal2(void* lpParameter);
int main(void)
{
	//::InitializeCriticalSection(&cs);    //临界区
	hEvent = ::CreateEvent(nullptr,
							//True，	::WaitForSingleObject后手动重置为无信号ResetEvent(hEvent)，但并非原子操作,发令枪				
		false,              //FALSE，则该函数将创建自动重置事件对象，并且系统会在释放单个等待线程后自动将事件状态重置为无信号
		true,               //发信号通知事件对象的初始状态
		nullptr);           //name
	/*hMutex = ::CreateMutex(nullptr,false,"hyc");
	if (::GetLastError() == ERROR_ALREADY_EXISTS)  //单例，函数调用之前存在命名的事件对象
	{
		return 0;
	}*/
	HANDLE  hthread1 = ::CreateThread(
		nullptr,
		0,
		Terminal1,
		nullptr,
		0,
		nullptr);
	HANDLE hthread2 = ::CreateThread(
		nullptr,
		0,
		Terminal2,
		nullptr,
		0,
		nullptr);
	::CloseHandle(hthread1);
	::CloseHandle(hthread2);
	hthread1 = nullptr;
	hthread2 = nullptr;
	

	::Sleep(10000);
	/*::CloseHandle(hMutex);
	hMutex = nullptr;*/
	::CloseHandle(hEvent);
	hEvent = nullptr;
	//::DeleteCriticalSection(&cs);

	return 0;


}
unsigned long
WINAPI
Terminal1(void* lpParameter)
{
	while (true)
	{
		//::WaitForSingleObject(hMutex,INFINITE);
		::WaitForSingleObject(hEvent, INFINITE);
		
		//::EnterCriticalSection(&cs);

		//::ResetEvent(hEvent);
		if (tickets > 0)
		{
			::Sleep(30);
			
			wcout << L"Terminal_1 : " << tickets-- << endl;
			//::ReleaseMutex(hMutex);
			::SetEvent(hEvent);
			//::LeaveCriticalSection(&cs);

		}
		else
		{
			::SetEvent(hEvent);
			//::ReleaseMutex(hMutex);
			//::LeaveCriticalSection(&cs);
			break;
		}

	}
	
	return 0;
}
unsigned long
WINAPI
Terminal2(void* lpParameter)
{
	while (true)
	{
		//::WaitForSingleObject(hMutex,INFINITE);//等待时间，有信号再返回
		::WaitForSingleObject(hEvent, INFINITE); 
		//::ResetEvent(hEvent);       //无信号
		//::EnterCriticalSection(&cs);
		if (tickets > 0)
		{
			::Sleep(30);
			
			wcout << L"Terminal_2 : " << tickets-- << endl;
			//::LeaveCriticalSection(&cs);
			//::ReleaseMutex(hMutex);
			::SetEvent(hEvent);  //置信号

		}
		else
		{
			//::LeaveCriticalSection(&cs);
			::SetEvent(hEvent);
			//::ReleaseMutex(hMutex);
			break;
		}

	}

	return 0;
}
//Aplication->process,function->thread
//headle,内核对象，运行在内核