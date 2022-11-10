#ifndef TOPAZ_CORE_ALLOCATORS_LINEAR_HPP
#define TOPAZ_CORE_ALLOCATORS_LINEAR_HPP
#include "hdk/memory/memblk.hpp"
#include "hdk/concepts.hpp"
#include <span>
#include <cstddef>

namespace hdk
{
	/**
	 * @ingroup tz_core_allocators
	 * An allocator which operates on a pre-allocated buffer of variable size.
	 *
	 * On construction, the arena buffer is considered to be wholly uninitialised. Each allocationslowly fills the arena until there is not enough space for an allocation request, in which case the null block is returned.
	 */
	class linear_allocator
	{
	public:
		linear_allocator(std::span<std::byte> arena);
		linear_allocator(hdk::memblk arena);

		hdk::memblk allocate(std::size_t count);
		void deallocate(hdk::memblk blk);
		bool owns(hdk::memblk blk) const;
	private:
		std::byte* head();

		std::span<std::byte> arena;
		std::size_t cursor = 0;
	};

	static_assert(hdk::allocator<linear_allocator>);
}

#endif // TOPAZ_CORE_ALLOCATORS_LINEAR_HPP
