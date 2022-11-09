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
		CXX_STANDARD ${HDK_CXX_VERSION}
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
endfunction()
