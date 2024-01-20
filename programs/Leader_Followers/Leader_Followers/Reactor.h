//-------------------------------------------------------
//	Reactor.h.
//	08/30/2018.			by bubo.
//	08/31/2018.			last modified.
//-------------------------------------------------------
#pragma once

#ifndef _REACTOR_H
#define _REACTOR_H

//-------------------------------------------------------
//	headers...
//-------------------------------------------------------
#include <chrono>
#include "Event_Handler.h"
#include <set>
#include <map>
#include <memory>
#include <Winsock2.h>


//-------------------------------------------------------
namespace lf
{
	//-------------------------------------------------------
	class Reactor
	{
	public:
		// Register an <Event_Handler> of a 
		// particular <Event_Type>. 
		bool register_handler (std::shared_ptr<Event_Handler> eh, Event_Type et); 
		
		// Remove an <Event_Handler> of a 
		// particular <Event_Type>. 
		bool remove_handler (std::shared_ptr<Event_Handler> eh, Event_Type et);
		
		// Entry point into the reactive event loop. [blocked method]
		bool wait_for_event (std::chrono::milliseconds timeout);
		void handle_events(void);

	private:
		void fillout_fds(void);		

	private:
		std::map<Event_Type, std::map<unsigned long, std::weak_ptr<Event_Handler>>> _handlers;
		fd_set _readfds;
		fd_set _writefds;
	};

	//-------------------------------------------------------
}

//-------------------------------------------------------
#endif // !_REACTOR_H




