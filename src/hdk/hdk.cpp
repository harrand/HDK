#include "hdk/hdk.hpp"
// temp
//
#include "hdk/debug.hpp"

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
		detail::init.initialised = true;
	}

	void terminate()
	{
		hdk::assert(detail::init.initialised, "terminate() called but we are not initialised");
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
