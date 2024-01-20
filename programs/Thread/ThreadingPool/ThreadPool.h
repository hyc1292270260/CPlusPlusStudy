#pragma once
#include "ITask.h"
#include <Windows.h>
#include <vector>
#include <list>

using namespace std;

namespace threadpool
{
	//---------------------------------------------
	class ThreadPool
	{
	public:
		static ThreadPool* instance(void);
		static void destroy_instance(void);
		bool initialize(int max_quantity, int set_quantity);
		bool set_thread_count(int total_count);
		void shutdown(void);
		void add_task(Itask* task);
		void add_tasks(vector<Itask*> tasks);

	private:
		ThreadPool();
		~ThreadPool();
		ThreadPool(ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;

		static unsigned long __stdcall fnThreadProc(void* lpParameter);

	private:
		static ThreadPool* _threadpool;
		HANDLE _hExitEvent;
		HANDLE _hSemaphore;
		static HANDLE _hSingletonLock;
		static HANDLE _hTaskLock;
		std::list<Itask*> _tasks;
		int _max_thread_quantity;
		int _total_thread_quantity;
		int _current_available_threads;
	};

	//---------------------------------------------
}





