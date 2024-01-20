//-------------------------------------------------------
//	Reactor.cpp.
//	08/30/2018.			by bubo.
//	08/31/2018.			last modified.
//-------------------------------------------------------
#include "Reactor.h"
#include <algorithm>

//-------------------------------------------------------
bool 
lf::Reactor::register_handler(
	std::shared_ptr<Event_Handler> eh,
	Event_Type et)
{
	if (!eh)
		return false;

	_handlers[et][eh->get_handle()] = eh;

	return true;
}

//-------------------------------------------------------
bool
lf::Reactor::remove_handler(
	std::shared_ptr<Event_Handler> eh, 
	Event_Type et)
{
	if (!eh)
		return false;

	auto event_it = _handlers.find(et);
	if (event_it == _handlers.end())
		return false;
	
	auto eh_it = _handlers[et].find(eh->get_handle());
	if (eh_it == _handlers[et].end())
		return false;

	_handlers[et].erase(eh_it);

	return true;
}

//-------------------------------------------------------
bool
lf::Reactor::wait_for_event(std::chrono::milliseconds timeout)
{
	fillout_fds();

	if (::select(0, &_readfds, &_writefds, nullptr, nullptr) > 0)	
		return true;
	return false;
}

//-------------------------------------------------------
inline
void 
lf::Reactor::fillout_fds(void)
{
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);

	int index = 0;
	for (auto it : _handlers[Event_Type::READ_EVENT])
		_readfds.fd_array[index++] = static_cast<SOCKET>(it.first);
	_readfds.fd_count = index;

	index = 0;
	for (auto it : _handlers[Event_Type::WRITE_EVENT])
		_writefds.fd_array[index++] = static_cast<SOCKET>(it.first);
	_writefds.fd_count = index;
}

//-------------------------------------------------------
void 
lf::Reactor::handle_events(void)
{
	for (int i = 0; i < _readfds.fd_count; ++i)
	{
		if (FD_ISSET(_readfds.fd_array[i], &_readfds))
		{
			auto event_it = _handlers.find(Event_Type::READ_EVENT);
			if (event_it != _handlers.end())
			{
				auto eh_it = event_it->second.find(_readfds.fd_array[i]);
				if (eh_it != event_it->second.end())
					if (auto eh = eh_it->second.lock())
						if (eh->handle_event(this, eh_it->first, Event_Type::READ_EVENT) == 0)
							event_it->second.erase(eh_it);
			}
		}
	}

	for (int i = 0; i < _writefds.fd_count; ++i)
	{
		if (FD_ISSET(_writefds.fd_array[i], &_writefds))
		{
			auto event_it = _handlers.find(Event_Type::WRITE_EVENT);
			if (event_it != _handlers.end())
			{
				auto eh_it = event_it->second.find(_readfds.fd_array[i]);
				if (eh_it != event_it->second.end())
					if (auto eh = eh_it->second.lock())
						if (eh->handle_event(this, eh_it->first, Event_Type::WRITE_EVENT) == 0)
							event_it->second.erase(eh_it);
			}
		}
	}
}

//-------------------------------------------------------





