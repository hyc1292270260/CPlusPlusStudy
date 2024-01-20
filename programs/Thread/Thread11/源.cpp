#include<iostream>
#include <thread>
#include <chrono>                 //ʱ���
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
		//std::unique_lock<std::mutex>lckouter(mx);  //������������ת��
		while (true)
		{
			//mx.lock();
			/*std::unique_lock<std::mutex>lckinner;
			lckinner = std::move(lckouter);   //ת����*/
			//std::lock_guard<std::mutex> lck(mx);		//��������
			std::unique_lock<std::mutex> lck(mx);        //�Զ��ͷţ�
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
	t1.join();					//�ȴ�t1����
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


