#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;
mutex mx;
condition_variable cv;
int main(void) 
{
	thread t1([&](void)->void
	{
		wcout << L"T1 waiting for cv..." << endl;
		unique_lock<mutex>lck(mx);
		cv.wait(lck); 
		wcout << L"T1 has gotten cv..." << endl;
	});

	thread t2([&](void)->void
	{
		wcout << L"T2 waiting for cv..." << endl;
		unique_lock<mutex>lck(mx);
		cv.wait(lck);			//�ȴ��ͷ���������unlock		
		wcout << L"T2 has gotten cv..." << endl;
	});
	this_thread::sleep_for(chrono::seconds(5));
	cv.notify_one();			//����һ��wait������lock
	
	thread t3([&](void)->void
	{
		wcout << L"T3 waiting for cv..." << endl;
		unique_lock<mutex>lck(mx);
		cv.wait(lck);
		wcout << L"T3 has gotten cv..." << endl;
	});

	this_thread::sleep_for(chrono::seconds(5));
	cv.notify_all();			//ȫ�����ѣ����ε���lock����

	t1.join();
	t2.join();
	t3.join();

	return 0;
}