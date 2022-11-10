#ifndef TOPAZ_CORE_ALLOCATORS_FALLBACK_HPP
#define TOPAZ_CORE_ALLOCATORS_FALLBACK_HPP
#include "hdk/memory/memblk.hpp"
#include "hdk/concepts.hpp"

namespace hdk
{
	/**
	 * @ingroup hdk_core_allocators
	 * Implements @ref hdk::allocator
	 *
	 * A meta-allocator which will use a primary allocator, but fall-back to a secondary allocator upon failure. fallback_allocators can be chained together.
	 *
	 * Often, @ref hdk::Mallocator and @ref hdk::Nullallocator are useful secondary allocators.
	 * @tparam P Primary allocator type. This will always be used first.
	 * @tparam S Secondary allocator type. This will only be used if the primary allocator fails (such as returning a nullblk on allocate(...))
	 */
	template<hdk::allocator P, hdk::allocator S>
	class fallback_allocator : private P, private S
	{
	public:
		hdk::memblk allocate(std::size_t count)
		{
			hdk::memblk r = P::allocate(count);
			if(r.ptr == nullptr)
			{
				r = S::allocate(count);
			}
			return r;
		}

		void deallocate(hdk::memblk blk)
		{
			if(P::owns(blk))
			{
				P::deallocate(blk);
			}
			else
			{
				S::deallocate(blk);
			}
		}

		bool owns(hdk::memblk blk) const
		{
			return P::owns(blk) || S::owns(blk);
		}
	};
}

#endif // TOPAZ_CORE_ALLOCATORS_FALLBACK_HPP
