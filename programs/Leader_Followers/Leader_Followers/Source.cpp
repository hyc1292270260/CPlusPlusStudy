#include "ThreadSet.h"
#include "Event_Handler.h"
#include "Reactor.h"
#include <thread>
#include <windows.h>
using namespace lf;

class Read_Handler : public Event_Handler
{
public:
	virtual int handle_event(Reactor* reactor, unsigned int handle, Event_Type et) override
	{
		_socket = handle;
		// ... recv...
		// 1. start network. set up the connect socket to accept.
		// reactor->register_handler(...)
		return ;
	}

	// Hook method returns the I/O <HANDLE>. 
	virtual unsigned int get_handle(void) const override
	{
		return _socket;
	}

private:
	SOCKET _socket; // connecting socket.
};

// class Wirte_Handler...

int main(void)
{
	Reactor* reactor = new Reactor;
	ThreadSet* thread_set = new ThreadSet(std::shared_ptr<Reactor>(reactor));
	Read_Handler* accept_handler = new Read_Handler;
	reactor->register_handler(std::shared_ptr<Event_Handler>(accept_handler), Event_Type::ACCEPT_EVENT);

	for (auto i = 0; i < 10; ++i)
	{
		std::thread t([i, thread_set](void) -> void
		{
			thread_set->join(std::chrono::milliseconds(0), i + 10);
		});

		t.detach();
	}

	std::this_thread::sleep_for(std::chrono::seconds(36000));

	return 0;
}




