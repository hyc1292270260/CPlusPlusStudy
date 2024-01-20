#include<iostream>
#include <thread>
#include <future>

int main(void)
{
	//异步线程返回future
	/*
	std::future<int> fut1 = std::async([](void) ->int
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
	    return 3;

	});
	std::future<int> fut2 = std::async([](void) ->int
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return 5;

	});
	int result = fut1.get() + fut2.get();
	*/
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();   //关联
	std::thread t([&fut]() -> void
	{
		std::wcout << L"start working..." << std::endl;
		std::wcout << L"waiting for money..." << std::endl;
		int money = fut.get();
		std::wcout << L"got $" << money << L"money!";

	});
	std::this_thread::sleep_for(std::chrono::seconds(10));
	prom.set_value(100);
	t.join();
	
	return 0;

}