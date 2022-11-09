include(CMakeParseArguments)
include(cmake/configure.cmake)

function(hdk_add_library)
	cmake_parse_arguments(
		HDK_ADD_LIBRARY
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)
	add_library(${HDK_ADD_LIBRARY_TARGET}
		${HDK_ADD_LIBRARY_SOURCES}
	)

	hdk_configure_common(
		TARGET ${HDK_ADD_LIBRARY_TARGET}
	)

	target_link_libraries(${HDK_CONFIGURE_COMMON_TARGET} PUBLIC hdk)
endfunction()

function(hdk_add_executable)

endfunction()
