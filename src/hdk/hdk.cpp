#include "hdk/hdk.hpp"
#include "hdk/debug.hpp"
#include "hdk/job/job.hpp"

#undef assert

namespace hdk
{
	namespace detail
	{
		struct init_state
		{
			bool initialised = false;
		};

		static init_state init = {};
	}

	void initialise()
	{
		hdk::assert(!detail::init.initialised, "initialise() already initialised");
		hdk::detail::job_system_init();
		detail::init.initialised = true;
	}

	void terminate()
	{
		hdk::assert(detail::init.initialised, "terminate() called but we are not initialised");
		hdk::detail::job_system_term();
		detail::init.initialised = false;
	}

	namespace detail
	{
		bool is_initialised()
		{
			return detail::init.initialised;
		}
	}
}
