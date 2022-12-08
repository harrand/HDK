#ifndef HDK_JOB_JOB_HPP
#define HDK_JOB_JOB_HPP

// TODO: Configurable
#include "hdk/job/impl/stdasync/job.hpp"
#include "hdk/job/impl/threadpool_lfq/job.hpp"
#undef assert

namespace hdk
{
	/**
	 * @ingroup hdk_job
	 * Underlying job system. See @ref hdk::job_system_type for API.
	 */
	using job_system_t = hdk::impl::job_system_threadpool_lfq;

	namespace detail
	{
		void job_system_init();
		void job_system_term();
	}

	/**
	 * @ingroup hdk_job
	 * Retrieve the global job system.
	 */
	job_system_t& job_system();
}

#endif // HDK_JOB_JOB_HPP
