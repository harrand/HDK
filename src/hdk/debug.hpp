#ifndef HDK_DEBUG_HPP
#define HDK_DEBUG_HPP
#include <source_location>

namespace hdk
{
	namespace detail
	{
		struct format_string
		{
			const char* str;
			std::source_location loc;

			format_string(const char* str, std::source_location loc = std::source_location::current()):
			str(str), loc(loc){}
		};
	}

	template<typename... Args>
	void assert(bool condition, detail::format_string fmt, Args&&... args);
}

#include "hdk/debug.inl"
#endif // HDK_DEBUG_HPP
