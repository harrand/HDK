#ifndef HDK_PROFILE_HPP
#define HDK_PROFILE_HPP

#if HDK_PROFILE
	#define CONCAT_HDKPROF(a, b) CONCAT_INNER_HDKPROF(a, b)
	#define CONCAT_INNER_HDKPROF(a, b) a ## b

	#define UNIQUE_NAME(base) CONCAT_HDKPROF(base, __LINE__)
	#define HDK_PROFZONE(name, colour) ZoneNamedNC(UNIQUE_NAME(tracy_profvar), name, colour, true)
#else
	#define HDK_PROFZONE(name, colour)
#endif

#endif // HDK_PROFILE_HPP
