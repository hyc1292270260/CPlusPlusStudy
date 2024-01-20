#include<iostream>
#include <thread>
#include <chrono>                 //时间库
#include<mutex>

using namespace std;


void Terminal_1(int& tickets, mutex& mx);

int main(void)
{
	int tickets = 100;
	std::mutex mx;
	std::thread t1(Terminal_1, std::ref(tickets),std::ref(mx));
	std::thread t2([&tickets,&mx]()->void 
	{
		//std::unique_lock<std::mutex>lckouter(mx);  //互斥锁，可以转移
		while (true)
		{
			//mx.lock();
			/*std::unique_lock<std::mutex>lckinner;
			lckinner = std::move(lckouter);   //转移锁*/
			//std::lock_guard<std::mutex> lck(mx);		//锁的守卫
			std::unique_lock<std::mutex> lck(mx);        //自动释放，
			if (tickets > 0)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				wcout << L"Terminal_2 : " << tickets-- << endl;
				//mx.unlock();
			}
			else
			{
				//mx.unlock();
				break;
			}
		}
		return;

	});
	t1.join();					//等待t1结束
	t2.join();
	return 0;

}
void Terminal_1(int& tickets,mutex& mx)
{
	while (true)
	{
		mx.lock();
		if (tickets > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
			wcout << L"Terminal_1 : " << tickets-- << endl;
			mx.unlock();
		}
		else
		{
			mx.unlock();
			break;
		}
	}
	return;
}


