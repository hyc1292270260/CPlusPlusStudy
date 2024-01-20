//-------------------------------------------------------
//	ThreadSet.h.
//	08/30/2018.			by bubo.
//	09/01/2018.			last modified.
//-------------------------------------------------------
#include "ThreadSet.h"
#include "Reactor.h"

//-------------------------------------------------------
lf::ThreadSet::ThreadSet(std::shared_ptr<Reactor> reactor)
{
	_reactor = reactor;
}

//-------------------------------------------------------
int 
lf::ThreadSet::join(
	std::chrono::milliseconds timeout, 
	unsigned int current_id)
{
	std::unique_lock<std::mutex> clk(_mutex);

	while (true)
	{
		// try to become the leader to process transactions.
		while (_leader_thread != NO_CURRENT_LEADER)
			_followers_condition.wait(clk);
		
		// become the leader.
		_leader_thread = current_id;

		// Leave monitor temporarily to allow other 
		// follower threads to join the set. guard.release ();
		// Run the reactor to dispatch the <handle_event> 
		// hook method associated with the next event. 

		if (!_reactor->wait_for_event(std::chrono::milliseconds(0))) 
			return -1;

		promote_new_leader();
		_reactor->handle_events();
	}

	

	return 0;
}

//-------------------------------------------------------
int 
lf::ThreadSet::promote_new_leader(void)
{
	_leader_thread = NO_CURRENT_LEADER;
	_followers_condition.notify_one();
	return 0;
}

//-------------------------------------------------------





