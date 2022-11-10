#ifndef HDK_JOB_API_JOB_HPP
#define HDK_JOB_API_JOB_HPP
#include <functional>
#include "hdk/data/handle.hpp"

namespace hdk
{
	namespace detail
	{
		struct job_handle_tag{};
	}
	using job_handle = hdk::handle<detail::job_handle_tag>;

	template<typename T>
	concept job_system_type = requires(T t, std::function<void()> job, job_handle jh)
	{
		{t.execute(job)} -> std::same_as<job_handle>;
		{t.complete(jh)} -> std::same_as<bool>;
		{t.any_work_remaining()} -> std::same_as<bool>;
		{t.size()} -> std::same_as<unsigned int>;
	};
}

#endif // HDK_JOB_API_JOB_HPP
