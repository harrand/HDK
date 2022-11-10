#ifndef TOPAZ_CORE_ALLOCATORS_NULL_HPP
#define TOPAZ_CORE_ALLOCATORS_NULL_HPP
#include "hdk/memory/memblk.hpp"
#include "hdk/concepts.hpp"

namespace hdk
{
	/**
	 * @ingroup hdk_core_allocators
	 * An allocator which always returns nullptr.
	 */
	class null_allocator
	{
	public:
		constexpr null_allocator() = default;
		constexpr hdk::memblk allocate(std::size_t count) const{return hdk::nullblk;}
		constexpr void deallocate(hdk::memblk blk) const{}
		constexpr bool owns(hdk::memblk blk) const{return blk == hdk::nullblk;}
	};

	static_assert(hdk::allocator<null_allocator>);
}

#endif // TOPAZ_CORE_ALLOCATORS_NULL_HPP
