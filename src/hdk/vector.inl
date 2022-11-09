#include "hdk/debug.hpp"
#include <utility>
#include <cmath>
#include <algorithm>

namespace hdk
{
	template<hdk::numeric T, std::size_t S>
	constexpr vector<T, S>::vector(std::array<T, S> data): vec(data){}

	template<hdk::numeric T, std::size_t S>
	const T& vector<T, S>::operator[](std::size_t idx) const
	{
		hdk::assert(idx < S, "vector<T, %zu>::operator[%zu]: Index out of range!", S, idx);
		return this->vec[idx];
	}

	template<hdk::numeric T, std::size_t S>
	T& vector<T, S>::operator[](std::size_t idx)
	{
		hdk::assert(idx < S, "vector<T, %zu>::operator[%zu]: Index out of range!", S, idx);
		return this->vec[idx];
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S>& vector<T, S>::operator+=(const vector<T, S>& rhs)
	{
		for(std::size_t i = 0; i < S; i++)
			this->vec[i] += rhs.vec[i];
		return *this;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S> vector<T, S>::operator+(const vector<T, S>& rhs) const
	{
		vector<T, S> copy = *this;
		copy += rhs;
		return copy;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S>& vector<T, S>::operator-=(const vector<T, S>& rhs)
	{
		for(std::size_t i = 0; i < S; i++)
			this->vec[i] -= rhs.vec[i];
		return *this;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S> vector<T, S>::operator-(const vector<T, S>& rhs) const
	{
		vector<T, S> copy = *this;
		copy -= rhs;
		return copy;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S>& vector<T, S>::operator*=(T scalar)
	{
		for(std::size_t i = 0; i < S; i++)
			this->vec[i] *= scalar;
		return *this;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S> vector<T, S>::operator*(T scalar) const
	{
		vector<T, S> copy = *this;
		copy *= scalar;
		return copy;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S>& vector<T, S>::operator/=(T scalar)
	{
		for(std::size_t i = 0; i < S; i++)
			this->vec[i] /= scalar;
		return *this;
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S> vector<T, S>::operator/(T scalar) const
	{
		vector<T, S> copy = *this;
		copy /= scalar;
		return copy;
	}

	template<hdk::numeric T, std::size_t S>
	bool vector<T, S>::operator==(const vector<T, S>& rhs) const
	{
		for(std::size_t i = 0; i < S; i++)
		{
			if constexpr(std::is_integral_v<T>)
			{
				// If we're some integer type
				if(!std::cmp_equal(this->vec[i], rhs[i]))
				{
					return false;
				}
			}
			else
			{
				// Float or double
				if(std::fabs(this->vec[i] - rhs[i]) > std::numeric_limits<T>::epsilon())
				{
					return false;
				}
			}
		}
		return true;
	}

	template<hdk::numeric T, std::size_t S>
	std::span<const T> vector<T, S>::data() const
	{
		return this->vec;
	}

	template<hdk::numeric T, std::size_t S>
	std::span<T> vector<T, S>::data()
	{
		return this->vec;
	}

	template<hdk::numeric T, std::size_t S>
	T vector<T, S>::dot(const vector<T, S>& rhs) const
	{
		T sum = T();
		for(std::size_t i = 0; i < S; i++)
		{
			sum += ((*this)[i] * rhs[i]);
		}
		return sum;
	}

	template<hdk::numeric T, std::size_t S>
	T vector<T, S>::length() const
	{
		T sum_squares = T();
		for(std::size_t i = 0; i < S; i++)
		{
			sum_squares += (*this)[i] * (*this)[i];
		}
		return std::sqrt(sum_squares);
	}

	template<hdk::numeric T, std::size_t S>
	void vector<T, S>::normalise()
	{
		T l = this->length();
		if(l == T{}) [[unlikely]]
		{
			return;
		}
		for(auto& d : this->vec)
		{
			d /= l;
		}
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S> vector<T, S>::normalised() const
	{
		vector<T, S> cpy = *this;
		cpy.normalise();
		return cpy;
	}

	template<hdk::numeric T, std::size_t S>
	template<int... indices>
	vector<T, sizeof...(indices)> vector<T, S>::swizzle() const
	{
		std::array<int, sizeof...(indices)> data_unswizzled{indices...};
		std::array<T, sizeof...(indices)> data{indices...};
		for(std::size_t i = 0; i < sizeof...(indices); i++)
		{
			data[i] = this->vec[data_unswizzled[i]];
		}
		return {data};
	}

	template<hdk::numeric T, std::size_t S>
	vector<T, S + 1> vector<T, S>::with_more(T&& end) const
	{
		std::array<T, S + 1> new_data;
		std::copy(this->vec.begin(), this->vec.end(), new_data.begin());
		new_data.back() = end;
		return {new_data};
	}

	template<hdk::numeric T, std::size_t S>
	template<std::size_t S2>
	vector<T, S + S2> vector<T, S>::with_more(const vector<T, S2>& end) const
	{
		std::array<T, S + S2> new_data;
		std::copy(this->vec.begin(), this->vec.end(), new_data.begin());
		std::copy(end.vec.begin(), end.vec.end(), new_data.begin() + S);
		return {new_data};
	}

	template<hdk::numeric T, std::size_t S>
	template<hdk::numeric X, typename>
	vector<T, S>::operator vector<X, S>() const
	{
		std::array<X, S> different_data;
		std::transform(this->vec.begin(), this->vec.end(), different_data.begin(), [](const T& t){return static_cast<X>(t);});
		return {different_data};
	}

	template<hdk::numeric T>
	vector<T, 3> cross(const vector<T, 3>& lhs, const vector<T, 3>& rhs)
	{
		vector<T, 3> ret;
		//cx = aybz − azby
		ret[0] = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
		//cy = azbx − axbz
		ret[1] = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
		//cz = axby − aybx
		ret[2] = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
		return ret;
	}

}
