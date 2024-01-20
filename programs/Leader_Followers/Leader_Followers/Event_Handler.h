//-------------------------------------------------------
//	Event_Handler.h.
//	08/30/2018.			by bubo.
//	08/30/2018.			last modified.
//-------------------------------------------------------
#pragma once

#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

//-------------------------------------------------------
//	headers.
//-------------------------------------------------------
#include <memory>

//-------------------------------------------------------
namespace lf
{
	//-------------------------------------------------------
	//	incomplete types.
	//-------------------------------------------------------
	class Reactor;

	//-------------------------------------------------------
	enum class Event_Type
	{
		ACCEPT_EVENT = 01, // ACCEPT_EVENT is an alias for READ_EVENT.
		READ_EVENT = 01,
		WRITE_EVENT = 02,
		TIMEOUT_EVENT = 04,
		SIGNAL_EVENT = 010,
		CLOSE_EVENT = 020
	};

	//-------------------------------------------------------
	class Event_Handler 
	{
	public:
		// Hook method dispatched by a <Reactor> to 
		// handle events of a particular type. 
		virtual int handle_event(Reactor* reactor, unsigned int handle, Event_Type et) = 0;

		// Hook method returns the I/O <HANDLE>. 
		virtual unsigned int get_handle(void) const = 0;
	};

	//-------------------------------------------------------
}

//-------------------------------------------------------
#endif // !_EVENT_HANDLER_H





