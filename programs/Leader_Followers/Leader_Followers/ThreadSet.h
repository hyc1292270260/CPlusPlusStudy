//-------------------------------------------------------
//	ThreadSet.h.
//	08/30/2018.			by bubo.
//	08/31/2018.			last modified.
//-------------------------------------------------------
#pragma once

#ifndef _THREADSET_H
#define _THREADSET_H

/*	-------------------------------------------------------
 @ Comments:
 Handles and handle sets: Handles identify I/O resources, such as socket connections or open files,
 which are often implemented and managed by an operating system.
 A handle set is a collection of I/O handles that can be used to wait for events to occur on handles in the set.
 A handle set returns to its caller when it is possible to initiate an operation on a handle in the set
 without the operation blocking.
 句柄和句柄集：句柄标识I / O资源，例如套接字连接或打开文件，这些资源通常由操作系统实现和管理。
 句柄集是I / O句柄的集合，可用于等待集合中句柄上发生的事件。
 当可以在没有操作阻塞的情况下对集合中的句柄启动操作时，句柄集返回其调用者。
 @ For example:
 OLTP servers are interested in two types of events – CONNECTION events and READ events – which represent
 incoming connections and transaction requests, respectively. Both front-end and back-end servers maintain
 a separate connection for each client. Each connection is represented in a server by a separate socket handle.
 Our OLTP servers use the select [3] event demultiplexer, which identifies handles that have events pending,
 so that applications can invoke I/O operations on handles without blocking calling threads.
 However, multiple threads cannot call select on the same handle set simultaneously because more than one
 thread will be notified erroneously that I/O events are pending.
 OLTP服务器对两种类型的事件感兴趣 -  CONNECTION事件和READ事件 - 分别代表传入连接和事务请求。前端服务器和后端服务器都为每个客户端维护单独的连接。每个连接在服务器中由单独的套接字句柄表示。
 我们的OLTP服务器使用select [3]事件解复用器，它识别具有待处理事件的句柄，以便应用程序可以在不阻塞调用线程的情况下调用句柄上的I / O 操作。
 但是，多个线程无法同时在同一个句柄集上调用select，因为将错误地通知多个线程I / O 事件处于挂起状态。

-------------------------------------------------------	*/

//-------------------------------------------------------
//	headers.
//-------------------------------------------------------
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <memory>

#define NO_CURRENT_LEADER 0u

//-------------------------------------------------------
namespace lf
{
	//-------------------------------------------------------
	//	incomplete types.
	//-------------------------------------------------------
	class Reactor;

	//-------------------------------------------------------
	class ThreadSet
	{
	public:
		ThreadSet(std::shared_ptr<Reactor> reactor);

		// Application threads invoke the join method to wait to demultiplex and dispatch new I / O events.
		// This method blocks until the application terminates or a timeout occurs. 
		int join(std::chrono::milliseconds timeout, unsigned int current_id);

		// The promote new leader method is invoked by server concrete event handlers before they perform 
		// application specific event processing.
		int promote_new_leader(void);

	private:
		// Pointer to the event demultiplexer / dispatcher. 
		std::shared_ptr<Reactor> _reactor;

		// The thread id of the leader thread, which is 
		// set to NO_CURRENT_LEADER if there is no leader. 
		unsigned long _leader_thread;

		// Follower threads wait on this condition variable until they are promoted to leader.
		std::condition_variable _followers_condition;

		// Serialize access to our internal state.
		std::mutex _mutex;
	};

	//-------------------------------------------------------
}

//-------------------------------------------------------
#endif // !_THREADSET_H





