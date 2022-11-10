#ifndef TOPAZ_CORE_ALLOCATORS_STACK_HPP
#define TOPAZ_CORE_ALLOCATORS_STACK_HPP
#include "hdk/memory/allocators/linear.hpp"

namespace hdk
{
	/**
	 * @ingroup tz_core_allocators
	 * An allocator which has its own fixed-size buffer on the stack from which memory is sub-allocated. Aside from operating on its own stack arena, a stack allocator behaves identically to a @ref linear_allocator.
	 *
	 * stack_allocators are excellent candidates for fallback allocators. `FallbackAllocator<stack_allocator<X>, Mallocator>` allows you to have small-size optimisation for free, for example.
	 * @tparam S Size of local automatic storage.
	 */
	template<std::size_t S>
	class stack_allocator : public linear_allocator
	{
	public:
		stack_allocator();
	private:
		alignas(alignof(std::max_align_t)) char data[S];
	};

	static_assert(hdk::allocator<stack_allocator<1>>);
}

#include "hdk/memory/allocators/stack.inl"
#endif // TOPAZ_CORE_ALLOCATORS_STACK_HPP
