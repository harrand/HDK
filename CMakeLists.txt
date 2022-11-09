cmake_minimum_required(VERSION 3.21)

project(hdk
	LANGUAGES CXX
	VERSION 1.0.0
	DESCRIPTION "C++ Application Framework"
)

set(HDK_CXX_VERSION 20)
include(cmake/project.cmake)

add_library(hdk
	src/hdk/hdk.hpp
	src/hdk/hdk.cpp
)
hdk_configure_common(TARGET hdk)
target_include_directories(hdk PUBLIC "${PROJECT_SOURCE_DIR}/src")
message("Build Type: ${CMAKE_BUILD_TYPE}")
