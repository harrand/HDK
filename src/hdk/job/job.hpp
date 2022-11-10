#ifndef HDK_JOB_JOB_HPP
#define HDK_JOB_JOB_HPP

// TODO: Configurable
#include "hdk/job/impl/stdasync/job.hpp"

namespace hdk
{
	using job_system_t = hdk::impl::job_system_stdasync;

	job_system_t& job_system();
}

#endif // HDK_JOB_JOB_HPP
