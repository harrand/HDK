#ifndef TOPAZ_CORE_ALLOCATORS_MALLOC_HPP
#define TOPAZ_CORE_ALLOCATORS_MALLOC_HPP
#include "hdk/memory/memblk.hpp"
#include "hdk/concepts.hpp"

namespace hdk
{
	/**
	 * @ingroup tz_core_allocators
	 * Implements @ref tz:Allocator
	 *
	 * An allocator which simply calls malloc. It thinks it owns all memory, so if you're using this in a @ref tz::FallbackAllocator make sure it is always used as a secondary allocator, never the primary (or you will `free()` no matter what).
	 */
	class mallocator
	{
	public:
		constexpr mallocator() = default;
		hdk::memblk allocate(std::size_t count) const;
		void deallocate(hdk::memblk blk) const;
		bool owns(hdk::memblk blk) const;
	};

	static_assert(hdk::allocator<mallocator>);
}

#endif // TOPAZ_CORE_ALLOCATORS_MALLOC_HPP
