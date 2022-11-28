#include "hdk/job/job.hpp"
#include "hdk/debug.hpp"
#include <memory>

namespace hdk
{
	std::unique_ptr<job_system_t> sys = nullptr;

	namespace detail
	{
		void job_system_init()
		{
			sys = std::make_unique<job_system_t>();
		}

		void job_system_term()
		{
			sys = nullptr;
		}
	}

	job_system_t& job_system()
	{
		hdk::assert(sys != nullptr);
		return *sys;
	}
}
