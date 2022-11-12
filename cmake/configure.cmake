include(CMakeParseArguments)

function(hdk_configure_common)
	cmake_parse_arguments(
		HDK_CONFIGURE_COMMON
		""
		"TARGET"
		""
		${ARGN}
	)

	set_target_properties(${HDK_CONFIGURE_COMMON_TARGET} PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
endfunction()

function(hdk_configure_debug)
	cmake_parse_arguments(
		HDK_CONFIGURE_DEBUG
		""
		"TARGET"
		""
		${ARGN}
	)

	if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${HDK_CONFIGURE_DEBUG_TARGET} PUBLIC /Zi)
	else()
		target_compile_options(${HDK_CONFIGURE_DEBUG_TARGET} PUBLIC -g -Og)
	endif()

endfunction()

function(hdk_configure_release)
	cmake_parse_arguments(
		HDK_CONFIGURE_RELEASE
		""
		"TARGET"
		""
		${ARGN}
	)

	target_compile_options(${HDK_CONFIGURE_RELEASE_TARGET}
		PRIVATE
		-O3
	)

endfunction()
