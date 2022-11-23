#ifndef HDK_PROFILE_HPP
#define HDK_PROFILE_HPP
#include "tracy/Tracy.hpp"
#include "common/TracySystem.hpp"
#undef assert

#if HDK_PROFILE
	#define CONCAT_HDKPROF(a, b) CONCAT_INNER_HDKPROF(a, b)
	#define CONCAT_INNER_HDKPROF(a, b) a ## b

	#define UNIQUE_NAME(base) CONCAT_HDKPROF(base, __LINE__)
	#define HDK_PROFZONE(name, colour) ZoneNamedNC(UNIQUE_NAME(tracy_profvar), name, colour, true)
	#define HDK_THREAD(name) tracy::SetThreadName(name)
	#define HDK_FRAME FrameMark
#else
	#define HDK_PROFZONE(name, colour)
	#define HDK_THREAD(name)
	#define HDK_FRAME
#endif

#endif // HDK_PROFILE_HPP
