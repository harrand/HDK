include(CMakeParseArguments)
include(cmake/configure.cmake)

function(hdk_base_add_library)
	cmake_parse_arguments(
		HDK_BASE_ADD_LIBRARY
		""
		"TARGET;BASE"
		"SOURCES"
		${ARGN}
	)
	
	cmake_language(EVAL CODE
	"
		add_library(${HDK_BASE_ADD_LIBRARY_TARGET} STATIC
			${HDK_BASE_ADD_LIBRARY_SOURCES})

		hdk_configure_common(
			TARGET ${HDK_BASE_ADD_LIBRARY_TARGET}
		)

	target_link_libraries(${HDK_BASE_ADD_LIBRARY_TARGET} PUBLIC ${HDK_BASE_ADD_LIBRARY_BASE})
	")
endfunction()

function(hdk_base_add_executable)
	cmake_parse_arguments(
		HDK_BASE_ADD_EXECUTABLE
		""
		"TARGET;BASE"
		"SOURCES"
		${ARGN}
	)
	
	add_executable(${HDK_BASE_ADD_EXECUTABLE_TARGET}
		${HDK_BASE_ADD_EXECUTABLE_SOURCES}
	)

	hdk_configure_common(
		TARGET ${HDK_BASE_ADD_EXECUTABLE_TARGET}
	)

target_link_libraries(${HDK_BASE_ADD_EXECUTABLE_TARGET} PUBLIC ${HDK_BASE_ADD_EXECUTABLE_BASE})
endfunction()

function(hdk_add_library)
	cmake_parse_arguments(
		HDK_ADD_LIBRARY
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_base_add_library(
		TARGET ${HDK_ADD_LIBRARY_TARGET}
		BASE hdk
	)
endfunction()

function(hdk_add_executable)
	cmake_parse_arguments(
		HDK_ADD_EXECUTABLE
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_base_add_executable(
		TARGET ${HDK_ADD_EXECUTABLE_TARGET}
		BASE hdk
		SOURCES ${HDK_ADD_EXECUTABLE_SOURCES}
	)

endfunction()
