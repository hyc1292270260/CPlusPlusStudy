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
		//ȷ������һ�������ж�����newΪԭ�Ӳ���
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
	_hSemaphore = ::CreateSemaphore(nullptr, 0, max_quantity, nullptr);//�ź�������ĳ�ʼ����,������
	if (!_hSemaphore)
		return false;
	//create threads
	HANDLE hthread = nullptr;
	for (int i = 0; i < total_quantity; ++i)
	{
		hthread = ::CreateThread(nullptr, 0, fnThreadProc, nullptr, 0, nullptr);   //��ջ�ĳ�ʼ��С�����ֽ�Ϊ��λ,0ΪĬ��
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
		if (::WaitForSingleObject(_threadpool->_hExitEvent, 0) == WAIT_OBJECT_0) /*�������δ�����źţ������������ȴ�״̬*/
		{
			
			break;
		}

		//get task and run

		while (true)
		{
			Itask* task = nullptr;
			::WaitForSingleObject(_hTaskLock, INFINITE);  //ȡ��ʱ����Ҫͬ��			
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
//�ź��������״̬�������������ʱ�����źţ����������������ʱ�����źš�
//��lInitialCount����ָ���ĳ�ʼ������������Զ����С��������lMaximumCount������ָ����ֵ��
//-----------------------------------------------------------------------------------------------------------
//ͨ����Ӧ�ó���ʹ���ź���������ʹ����Դ���߳��������߳�ʹ����Դ֮ǰ�����ڶ�����һ���ȴ������ĵ�����ָ���ź������ ��
//��wait��������ʱ�����Ὣ�ź����ļ�����һ��
//���߳�ʹ������Դ�������� ReleaseSemaphore���ź����ļ�������1��
