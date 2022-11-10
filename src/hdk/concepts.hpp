#ifndef HDK_CONCEPTS_HPP
#define HDK_CONCEPTS_HPP
#include "hdk/memory/memblk.hpp"
#include <concepts>
#include <type_traits>
#include <numeric>

namespace hdk
{
	template<typename T>
	concept numeric = requires
	{
		requires std::is_arithmetic_v<std::decay_t<T>>;
		requires !std::is_same_v<std::remove_cvref<T>, bool>;
		requires !std::is_same_v<std::remove_cvref<T>, char>;
	};

	template<typename T>
	concept allocator = requires(T t, hdk::memblk blk, std::size_t sz)
	{
		{t.allocate(sz)} -> std::same_as<hdk::memblk>;
		{t.deallocate(blk)} -> std::same_as<void>;
		{t.owns(blk)} -> std::same_as<bool>;
	};

}

#endif // HDK_CONCEPTS_HPP
