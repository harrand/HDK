#include "hdk/job/job.hpp"
#include <memory>

namespace hdk
{
	std::unique_ptr<job_system_t> sys = nullptr;

	job_system_t& job_system()
	{
		if(sys == nullptr)
		{
			sys = std::make_unique<job_system_t>();
		}

		return *sys;
	}
}
