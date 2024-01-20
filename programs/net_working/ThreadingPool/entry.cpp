#include"ThreadPool.h"
using namespace threadpool;

int main(void)
{
	ThreadPool::instance()->initialize(20,10);
	::Sleep(500);
	ThreadPool::instance()->set_thread_count(15);
	ThreadPool::instance()->shutdown(); 
	ThreadPool::instance()->destroy_instance();

	return 0;

}