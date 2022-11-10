#include "hdk/memory/allocators/malloc.hpp"
#include <cstdlib>

namespace hdk
{
	hdk::memblk mallocator::allocate(std::size_t count) const
	{
		void* addr = std::malloc(count);
		if(addr == nullptr)
		{
			return hdk::nullblk;
		}
		return
		{
			.ptr = addr,
			.size = count
		};
	}

	void mallocator::deallocate(hdk::memblk blk) const
	{
		std::free(blk.ptr);
	}

	bool mallocator::owns([[maybe_unused]] hdk::memblk blk) const
	{
		return true;
	}
}
