#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hMutex = nullptr;
HANDLE hEvent = nullptr;
CRITICAL_SECTION cs;  //�û������ٶȿ�
int tickets = 100;
unsigned long WINAPI Terminal1(void* lpParameter);
unsigned long WINAPI Terminal2(void* lpParameter);
int main(void)
{
	//::InitializeCriticalSection(&cs);    //�ٽ���
	hEvent = ::CreateEvent(nullptr,
							//True��	::WaitForSingleObject���ֶ�����Ϊ���ź�ResetEvent(hEvent)��������ԭ�Ӳ���,����ǹ				
		false,              //FALSE����ú����������Զ������¼����󣬲���ϵͳ�����ͷŵ����ȴ��̺߳��Զ����¼�״̬����Ϊ���ź�
		true,               //���ź�֪ͨ�¼�����ĳ�ʼ״̬
		nullptr);           //name
	/*hMutex = ::CreateMutex(nullptr,false,"hyc");
	if (::GetLastError() == ERROR_ALREADY_EXISTS)  //��������������֮ǰ�����������¼�����
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
		//::WaitForSingleObject(hMutex,INFINITE);//�ȴ�ʱ�䣬���ź��ٷ���
		::WaitForSingleObject(hEvent, INFINITE); 
		//::ResetEvent(hEvent);       //���ź�
		//::EnterCriticalSection(&cs);
		if (tickets > 0)
		{
			::Sleep(30);
			
			wcout << L"Terminal_2 : " << tickets-- << endl;
			//::LeaveCriticalSection(&cs);
			//::ReleaseMutex(hMutex);
			::SetEvent(hEvent);  //���ź�

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
//headle,�ں˶����������ں�