include(CMakeParseArguments)

function(hdk_add_test)
	cmake_parse_arguments(
		HDK_ADD_TEST
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_add_executable(
		TARGET ${HDK_ADD_TEST_TARGET}
		SOURCES ${HDK_ADD_TEST_SOURCES}
	)

	add_test(
		NAME ${HDK_ADD_TEST_TARGET}
		COMMAND ${HDK_ADD_TEST_TARGET}
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	)

	add_dependencies(hdktest_build ${HDK_ADD_TEST_TARGET})
	add_dependencies(hdktest ${HDK_ADD_TEST_TARGET})
	message(STATUS "Detected test ${HDK_ADD_TEST_TARGET}")
endfunction()

add_custom_target(hdktest_build)
add_custom_target(hdktest
	COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure --schedule-random -C -Debug
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
