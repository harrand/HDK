#ifndef TOPAZ_CORE_ALLOCATORS_ADAPTER_HPP
#define TOPAZ_CORE_ALLOCATORS_ADAPTER_HPP
#include "hdk/memory/memblk.hpp"
#include "hdk/concepts.hpp"
#include "hdk/debug.hpp"

namespace hdk
{
	/**
	 * @ingroup hdk_core_allocators
	 * A meta-allocator which allows a topaz allocator to be used as if it were a `std::allocator`. This means it can be used for standard-library containers.
	 *
	 * For instance:
	 * `std::vector<int, std::allocator<int>>` is functionally equivalent to `std::vector<int, hdk::allocator_adapter<int, hdk::Mallocator>>`
	 */
	template<typename T, hdk::allocator A>
	class allocator_adapter : private A
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		allocator_adapter() = default;
		allocator_adapter(const A& a):
		A(a){}

		template<class U>
		allocator_adapter(const allocator_adapter<U, A>& other){}

		T* allocate(std::size_t n)
		{
			hdk::memblk blk = A::allocate(n * sizeof(T));
			hdk::assert(blk != nullblk, "allocator_adapter -- The underlying topaz allocator returned a null-block. Memory allocation failed. The standard library allocator is going to crash.");
			return reinterpret_cast<T*>(blk.ptr);
		}

		void deallocate(T* p, std::size_t n)
		{
			A::deallocate({.ptr = p, .size = n});
		}
	};
}

#endif // TOPAZ_CORE_ALLOCATORS_ADAPTER_HPP
