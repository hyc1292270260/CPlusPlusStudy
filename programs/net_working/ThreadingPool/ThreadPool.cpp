#include "ThreadPool.h"
#include<windows.h>

HANDLE threadpool::ThreadPool::_hSingletonLock = ::CreateMutex(nullptr, false, nullptr);
threadpool::ThreadPool* threadpool::ThreadPool::_threadpool = nullptr;
HANDLE threadpool::ThreadPool::_hTaskLock = ::CreateMutex(nullptr, false, nullptr);
threadpool::ThreadPool*
threadpool::ThreadPool::instance(void)
{
	if (!_threadpool)
	{
		//确保建立一个对象，判断语句和new为原子操作
		::WaitForSingleObject(_hSingletonLock, INFINITE);
		if (!_threadpool)
			_threadpool = new ThreadPool;
		::ReleaseMutex(_hSingletonLock);
	}
	return _threadpool;
}

void threadpool::ThreadPool::destroy_instance(void)
{
	if (_threadpool)
	{
		::WaitForSingleObject(_hSingletonLock, INFINITE);
		if (_threadpool)
		{
			delete _threadpool;
			_threadpool = nullptr;
		}

		::ReleaseMutex(_hSingletonLock);
	}
}

bool
threadpool::ThreadPool::initialize(int max_quantity, int total_quantity)
{
	// create hSemaphore
	_hSemaphore = ::CreateSemaphore(nullptr, 0, max_quantity, nullptr);//信号量对象的初始计数,最大计数
	if (!_hSemaphore)
		return false;
	//create threads
	HANDLE hthread = nullptr;
	for (int i = 0; i < total_quantity; ++i)
	{
		hthread = ::CreateThread(nullptr, 0, fnThreadProc, nullptr, 0, nullptr);   //堆栈的初始大小，以字节为单位,0为默认
		::CloseHandle(hthread);
		hthread = nullptr;
	}
	// create exit event 
	_hExitEvent = ::CreateEvent(nullptr, true, false, nullptr);
	if (!_hExitEvent)
		return false;
	_max_thread_quantity = max_quantity;
	_total_thread_quantity = total_quantity;
	_current_available_threads = _total_thread_quantity;
	return true;
}

bool threadpool::ThreadPool::set_thread_count(int total_count)
{
	if (total_count > _max_thread_quantity || total_count < 0)
		return false;
	int dalte = total_count - _total_thread_quantity;
	if (dalte > 0)
	{
		//increae
		::WaitForSingleObject(_hTaskLock, INFINITE);
		//create new threads to threadpool
		HANDLE hthread = NULL;
		for (int i = 0; i < dalte; ++i)
		{
			hthread = ::CreateThread(nullptr, 0, fnThreadProc, nullptr, 0, nullptr);
			if (hthread)
			{
				::CloseHandle(hthread);
				++_current_available_threads;
				++_total_thread_quantity;
			}
		}

		::ReleaseMutex(_hTaskLock);
	}
	else if (dalte == 0)
		return true;
	else
	{
		//decrease
		::WaitForSingleObject(_hTaskLock, INFINITE);
		::SetEvent(_hExitEvent);
		::ReleaseSemaphore(_hSemaphore, -dalte, nullptr);
		while (total_count - _total_thread_quantity < 0)  //wait for
		{
			--_total_thread_quantity;
			::Sleep(100);
		}
		
		::ResetEvent(_hExitEvent);
		::ReleaseMutex(_hTaskLock);
		return true;
	}

}

void threadpool::ThreadPool::shutdown(void)
{
	::SetEvent(_hExitEvent);
	::ReleaseSemaphore(_hSemaphore, _total_thread_quantity, nullptr);
	while (_total_thread_quantity > 0)
		::Sleep(100);
	::CloseHandle(_hExitEvent);
	::CloseHandle(_hSemaphore);

}

void threadpool::ThreadPool::add_task(Itask* task)
{
	if (!task)
		return;
	::WaitForSingleObject(_hTaskLock, INFINITE);
	while (_current_available_threads = 0)
		::Sleep(100);
	::ReleaseSemaphore(_hSemaphore, 1, nullptr);
	::ReleaseMutex(_hTaskLock);
}

void threadpool::ThreadPool::add_task(vector<Itask*> tasks)
{

	if (tasks.size() == 0)
		return;

	::WaitForSingleObject(_hTaskLock, INFINITE);
	for (auto& it : tasks)
		tasks.push_back(it);
	if (_current_available_threads < _total_thread_quantity)
		::ReleaseSemaphore(_hSemaphore, _total_thread_quantity - _current_available_threads >
			tasks.size() ? tasks.size() : _total_thread_quantity - _current_available_threads, nullptr);

	::ReleaseMutex(_hTaskLock);
}
threadpool::ThreadPool::ThreadPool() :_max_thread_quantity(0), _total_thread_quantity(0), _current_available_threads(0)
{
}

threadpool::ThreadPool::~ThreadPool()
{
}


unsigned long __stdcall
threadpool::ThreadPool::fnThreadProc(void * lpParameter)
{
	while (true)
	{

		::WaitForSingleObject(_threadpool->_hSemaphore, INFINITE);
		
		--_threadpool->_current_available_threads;
		//check exit
		if (::WaitForSingleObject(_threadpool->_hExitEvent, 0) == WAIT_OBJECT_0) /*如果对象未发出信号，则函数不会进入等待状态*/
		{
			
			break;
		}

		//get task and run

		while (true)
		{
			Itask* task = nullptr;
			::WaitForSingleObject(_hTaskLock, INFINITE);  //取的时候需要同步			
			if (_threadpool->_tasks.size() > 0)
			{
				auto task = _threadpool->_tasks.front();
				_threadpool->_tasks.pop_front();
				::ReleaseMutex(_hTaskLock);
				task->run();
				delete task;
			}
			else
			{
				::ReleaseMutex(_hTaskLock);
				break;
			}

		}
		++_threadpool->_current_available_threads;
	}

	++_threadpool->_total_thread_quantity;
	return 0;
}
//信号量对象的状态在其计数大于零时发出信号，并在其计数等于零时发出信号。
//该lInitialCount参数指定的初始计数。计数永远不会小于零或大于lMaximumCount参数中指定的值。
//-----------------------------------------------------------------------------------------------------------
//通常，应用程序使用信号量来限制使用资源的线程数。在线程使用资源之前，它在对其中一个等待函数的调用中指定信号量句柄 。
//当wait函数返回时，它会将信号量的计数减一。
//当线程使用完资源后，它调用 ReleaseSemaphore将信号量的计数增加1。
