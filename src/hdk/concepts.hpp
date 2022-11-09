#ifndef HDK_CONCEPTS_HPP
#define HDK_CONCEPTS_HPP
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
}

#endif // HDK_CONCEPTS_HPP
