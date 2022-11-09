#ifndef HDK_HPP
#define HDK_HPP

namespace hdk
{
	void initialise();
	void terminate();

	namespace detail
	{
		bool is_initialised();
	}

}

#endif // HDK_HPP
