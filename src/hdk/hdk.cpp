#include "hdk/hdk.hpp"

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
		detail::init.initialised = true;
	}

	void terminate()
	{
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
