#ifndef HDK_JOB_JOB_HPP
#define HDK_JOB_JOB_HPP

// TODO: Configurable
#include "hdk/job/impl/stdasync/job.hpp"

namespace hdk
{
	/**
	 * @ingroup hdk_job
	 * Underlying job system. See @ref hdk::job_system_type for API.
	 */
	using job_system_t = hdk::impl::job_system_stdasync;

	/**
	 * @ingroup hdk_job
	 * Retrieve the global job system.
	 */
	job_system_t& job_system();
}

#endif // HDK_JOB_JOB_HPP