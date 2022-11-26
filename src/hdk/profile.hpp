#ifndef HDK_PROFILE_HPP
#define HDK_PROFILE_HPP
#if HDK_PROFILE
#include "tracy/Tracy.hpp"
#include "common/TracySystem.hpp"
#include "client/TracyProfiler.hpp"
#endif
#undef assert

#if HDK_PROFILE
	#define CONCAT_HDKPROF(a, b) CONCAT_INNER_HDKPROF(a, b)
	#define CONCAT_INNER_HDKPROF(a, b) a ## b

	#define UNIQUE_NAME(base) CONCAT_HDKPROF(base, __LINE__)
	#define HDK_PROFZONE(name, colour) ZoneNamedNC(UNIQUE_NAME(tracy_profvar), name, colour, true)
	#define HDK_THREAD(name) tracy::SetThreadName(name)
	#define HDK_FRAME FrameMark
	#define HDK_FRAME_BEGIN FrameMarkStart("Frame Loop")
	#define HDK_FRAME_END FrameMarkEnd("Frame Loop")
#else
	#define HDK_PROFZONE(name, colour)
	#define HDK_THREAD(name)
	#define HDK_FRAME
	#define HDK_FRAME_BEGIN
	#define HDK_FRAME_END
#endif

#endif // HDK_PROFILE_HPP
