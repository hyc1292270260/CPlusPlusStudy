#pragma once

namespace threadpool
{
	class Itask
	{
	public:
		virtual void run(void) = 0;
	};
}
