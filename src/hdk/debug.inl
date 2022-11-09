#include <utility>
#include <cstdio>
#include <cstdlib>

namespace hdk
{
	template<typename... Args>
	void assert([[maybe_unused]] bool condition, [[maybe_unused]] detail::format_string fmt, [[maybe_unused]] Args&&... args)
	{
		#if HDK_DEBUG
			if(condition) return;
			std::fprintf(stderr, "Assert Failure: ");
			std::fprintf(stderr, fmt.str, std::forward<Args>(args)...);
			std::abort();
		#endif
	}
}
