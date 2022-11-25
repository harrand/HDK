#ifndef HDK_MEMORY_MEMBLK_HPP
#define HDK_MEMORY_MEMBLK_HPP
#include <cstddef>

namespace hdk
{
	/**
	* @ingroup hdk
	* A non-owning, contiguous block of memory.
	*/
	struct memblk
	{
		/// Start address of the block.
		void* ptr;
		/// Size of the block, in bytes.
		std::size_t size;
		
		bool operator==(const memblk& rhs) const = default;
	};
	/// Represents the null block.
	constexpr memblk nullblk{.ptr = nullptr, .size = 0};
}

#endif // HDK_MEMORY_MEMBLK_HPP
