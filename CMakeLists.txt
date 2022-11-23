cmake_minimum_required(VERSION 3.21)

project(hdk
	LANGUAGES CXX
	DESCRIPTION "C++ Application Framework"
	VERSION "1.1.0.1"
)

option(HDK_PROFILE "Whether profiling is enabled or not" 0)

include(cmake/project.cmake)
include(cmake/test.cmake)

find_package(Threads)

add_library(hdk STATIC
	src/hdk/data/handle.hpp
	src/hdk/data/vector.cpp
	src/hdk/data/vector.hpp
	src/hdk/data/vector.inl
	src/hdk/data/version.cpp
	src/hdk/data/version.hpp
	
	src/hdk/job/job.hpp
	src/hdk/job/job.cpp
	src/hdk/job/api/job.hpp
	src/hdk/job/impl/stdasync/job.cpp
	src/hdk/job/impl/stdasync/job.hpp
	src/hdk/job/impl/threadpool_lfq/job.cpp
	src/hdk/job/impl/threadpool_lfq/job.hpp

	src/hdk/memory/allocators/adapter.hpp
	src/hdk/memory/allocators/fallback.hpp
	src/hdk/memory/allocators/linear.cpp
	src/hdk/memory/allocators/linear.hpp
	src/hdk/memory/allocators/malloc.cpp
	src/hdk/memory/allocators/malloc.hpp
	src/hdk/memory/allocators/null.hpp
	src/hdk/memory/allocators/stack.hpp
	src/hdk/memory/allocators/stack.inl
	src/hdk/memory/clone.hpp
	src/hdk/memory/memblk.hpp

	src/hdk/concepts.hpp
	src/hdk/debug.cpp
	src/hdk/debug.hpp
	src/hdk/hdk.hpp
	src/hdk/hdk.cpp
	src/hdk/macros.hpp
	src/hdk/profile.hpp
)
hdk_configure_common(TARGET hdk)
target_include_directories(hdk PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_compile_definitions(hdk PRIVATE "-DHDK_VER=0x${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}${PROJECT_VERSION_TWEAK}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_compile_definitions(hdk PUBLIC "-DHDK_DEBUG=1")
	hdk_configure_debug(TARGET hdk)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	target_compile_definitions(hdk PUBLIC "-DHDK_DEBUG=0")
	hdk_configure_release(TARGET hdk)
else()
	message(FATAL_ERROR "CMAKE_BUILD_TYPE not recognised \"${CMAKE_BUILD_TYPE}\"")
endif()

if(${HDK_PROFILE} EQUAL 1)
	message(STATUS "HDK - Profiling enabled in this build")
	target_compile_definitions(hdk PUBLIC "-DHDK_PROFILE=1")
	hdk_configure_profile(TARGET hdk)
else()
	message(STATUS "HDK - Profiling disabled in this build")
	target_compile_definitions(hdk PUBLIC "-DHDK_PROFILE=0")
endif()

add_subdirectory(vendor)
target_link_libraries(hdk PRIVATE debugbreak Threads::Threads)
target_link_libraries(hdk PUBLIC textc_lib concurrentqueue)

include(cmake/text.cmake)

enable_testing()
add_subdirectory(test)
