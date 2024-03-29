#ifndef HDK_DATA_HANDLE_HPP
#define HDK_DATA_HANDLE_HPP
#include <cstddef>
#include <limits>
#include <type_traits>

namespace hdk
{
	enum class hanval : std::size_t{};

	struct nullhand_t{};
	constexpr nullhand_t nullhand;

	template<typename T>
	class handle
	{
	public:
		handle(hanval v):
		value(v){}

		handle([[maybe_unused]] nullhand_t nh = {}):
		value(static_cast<hanval>(std::numeric_limits<std::underlying_type_t<hanval>>::max())){}

		explicit operator hanval() const
		{
			return this->value;
		}

		handle& operator=(hanval value)
		{
			this->value = value;
			return *this;
		}

		bool operator==(nullhand_t) const
		{
			return handle<T>{nullhand}.value == this->value;
		}
		bool operator!=(nullhand_t) const
		{
			return handle<T>{nullhand}.value != this->value;
		}

		bool operator==(const handle<T>& rhs) const = default;
		bool operator!=(const handle<T>& rhs) const = default;
	private:
		hanval value;
	};
}

#endif // HDK_DATA_HANDLE_HPP
