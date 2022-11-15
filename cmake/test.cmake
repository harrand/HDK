include(CMakeParseArguments)

function(hdk_base_add_test_harness)
	cmake_parse_arguments(
		HDK_BASE_ADD_TEST_HARNESS
		""
		"BASE_NAME"
		""
		${ARGN}
	)

	cmake_language(EVAL CODE
	"
	add_custom_target(${HDK_BASE_ADD_TEST_HARNESS_BASE_NAME}test_build)
	add_custom_target(${HDK_BASE_ADD_TEST_HARNESS_BASE_NAME}test
		COMMAND \"${CMAKE_CTEST_COMMAND}\" --output-on-failure --schedule-random -L \"${HDK_BASE_ADD_TEST_HARNESS_BASE_NAME}\"
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		)
	")
	
endfunction()

function(hdk_base_add_test)
	cmake_parse_arguments(
		HDK_BASE_ADD_TEST
		""
		"TARGET;BASE_NAME"
		"SOURCES"
		${ARGN}
	)

	cmake_language(EVAL CODE
	"
		${HDK_BASE_ADD_TEST_BASE_NAME}_add_executable(
			TARGET ${HDK_BASE_ADD_TEST_TARGET}
			SOURCES ${HDK_BASE_ADD_TEST_SOURCES}
		)

		add_test(
			NAME ${HDK_BASE_ADD_TEST_TARGET}
			COMMAND ${HDK_BASE_ADD_TEST_TARGET}
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		)
		set_tests_properties(${HDK_BASE_ADD_TEST_TARGET} PROPERTIES LABELS \"${HDK_BASE_ADD_TEST_BASE_NAME}\")

		add_dependencies(${HDK_BASE_ADD_TEST_BASE_NAME}test_build ${HDK_BASE_ADD_TEST_TARGET})
		add_dependencies(${HDK_BASE_ADD_TEST_BASE_NAME}test ${HDK_BASE_ADD_TEST_TARGET})
		message(STATUS \"${HDK_BASE_ADD_TEST_BASE_NAME} - Detected test ${HDK_BASE_ADD_TEST_TARGET}\")
	")
	
endfunction()

function(hdk_add_test)
	cmake_parse_arguments(
		HDK_ADD_TEST
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_base_add_test(
		TARGET ${HDK_ADD_TEST_TARGET}
		BASE_NAME hdk
		SOURCES ${HDK_ADD_TEST_SOURCES}
	)
endfunction()
hdk_base_add_test_harness(BASE_NAME hdk)
