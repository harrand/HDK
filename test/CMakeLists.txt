hdk_add_test(
	TARGET hdk_init_test
	SOURCES hdk_init_test.cpp
)

hdk_add_test(
	TARGET hdk_text_test
	SOURCES hdk_text_test.cpp
)
hdk_attach_text(
	TARGET hdk_text_test
	TEXTS test/test_file.txt
)

hdk_add_test(
	TARGET hdk_vector_test
	SOURCES hdk_vector_test.cpp
)
