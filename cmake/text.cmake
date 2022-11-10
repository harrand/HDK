include(CMakeParseArguments)

function(hdk_attach_text)
	cmake_parse_arguments(
		HDK_ATTACH_TEXT
		""
		"TARGET"
		"TEXTS"
		${ARGN}
	)

	add_text(
		TARGET ${HDK_ATTACH_TEXT_TARGET}
		INPUT_DIR ${PROJECT_SOURCE_DIR}
		OUTPUT_DIR ${PROJECT_BINARY_DIR}
		TEXT_FILES ${HDK_ATTACH_TEXT_TEXTS}
	)
endfunction()
