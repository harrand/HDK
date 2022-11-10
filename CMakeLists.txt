cmake_minimum_required(VERSION 3.21)

project(hdk
	LANGUAGES CXX
	DESCRIPTION "C++ Application Framework"
)

include(cmake/project.cmake)
include(cmake/test.cmake)

add_library(hdk STATIC
	src/hdk/concepts.hpp
	src/hdk/debug.cpp
	src/hdk/debug.hpp
	src/hdk/hdk.hpp
	src/hdk/hdk.cpp
	src/hdk/macros.hpp
	src/hdk/data/vector.cpp
	src/hdk/data/vector.hpp
	src/hdk/data/vector.inl
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
target_link_libraries(hdk PUBLIC textc_lib)

include(cmake/text.cmake)

enable_testing()
add_subdirectory(test)
