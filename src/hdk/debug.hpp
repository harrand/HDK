#ifndef HDK_DEBUG_HPP
#define HDK_DEBUG_HPP
#include <source_location>
#include <concepts>
#include <string>
#include <functional>

namespace hdk
{
	namespace detail
	{
		struct format_string
		{
			const char* str;
			std::source_location loc;

			constexpr format_string(const char* str, std::source_location loc = std::source_location::current()):
			str(str), loc(loc){}
		};
	}

	template<typename... Args>
	void assert(bool condition, detail::format_string fmt = "<No message>", Args&&... args);

	template<typename... Args>
	void error(detail::format_string fmt = "<No message>", Args&&... args);
}

#define hdk_legacy_assert(cond) hdk::assert(cond, "Legacy Assert Detected")

#include "hdk/debug.inl"
#endif // HDK_DEBUG_HPP
