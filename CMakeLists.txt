cmake_minimum_required(VERSION 3.21)

project(hdk
	LANGUAGES CXX
	VERSION 1.0.0
	DESCRIPTION "C++ Application Framework"
)

set(HDK_CXX_VERSION 20)
include(cmake/project.cmake)
include(cmake/test.cmake)

add_library(hdk STATIC
	src/hdk/debug.cpp
	src/hdk/debug.hpp
	src/hdk/hdk.hpp
	src/hdk/hdk.cpp
)
hdk_configure_common(TARGET hdk)
target_include_directories(hdk PUBLIC "${PROJECT_SOURCE_DIR}/src")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_compile_definitions(hdk PUBLIC "-DHDK_DEBUG=1")
else()
	target_compile_definitions(hdk PUBLIC "-DHDK_DEBUG=0")
endif()

add_subdirectory(vendor)
target_link_libraries(hdk PRIVATE debugbreak)

enable_testing()
add_subdirectory(test)
