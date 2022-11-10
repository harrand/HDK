#ifndef HDK_HPP
#define HDK_HPP

namespace hdk
{

	/**
	 * @defgroup hdk HDK
	 * Low-level C++ framework utilities.
	 */

	/**
	 * @ingroup hdk
	 * @defgroup hdk_init Initialisation and Termination
	 * Documentation for functionality related to HDK initialisation and termination.
	 */

	/**
	 * @ingroup hdk
	 * @defgroup hdk_job Job System
	 * Documentation for job-system.
	 */

	/**
	 * @ingroup hdk
	 * @defgroup hdk_memory Memory Utility
	 * Documentation for a grab-bag of memory helper structs, classes and functions.
	 */

	/**
	 * @ingroup hdk_memory
	 * @defgroup hdk_memory_allocator Allocators
	 * Documentation for bespoke memory allocators.
	 */

	/**
	 * @ingroup hdk_init
	 * Initialise HDK.
	 */
	void initialise();
	/**
	 * @ingroup hdk_init
	 * Terminate HDK.
	 */
	void terminate();

	namespace detail
	{
		bool is_initialised();
	}

	/*! @mainpage Home
	 * ## Introduction
	 *
	 * Welcome to the home page of the HDK documentation. Here you can find detailed information about the vast majority of modules, classes and functions within HDK.
	 */
}

#endif // HDK_HPP
