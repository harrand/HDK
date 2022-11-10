#ifndef HDK_MEMORY_MEMBLK_HPP
#define HDK_MEMORY_MEMBLK_HPP
#include <cstddef>

namespace hdk
{
	struct memblk
	{
		void* ptr;
		std::size_t size;
		
		bool operator==(const memblk& rhs) const = default;
	};
	constexpr memblk nullblk{.ptr = nullptr, .size = 0};
}

#endif // HDK_MEMORY_MEMBLK_HPP
