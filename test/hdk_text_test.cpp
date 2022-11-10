#include "hdk/hdk.hpp"
#include "hdk/macros.hpp"
#include "hdk/debug.hpp"
#include <string_view>
#include <cstdio>

#include ImportedTextHeader(test_file, txt)

int main()
{
	hdk::initialise();
	
	std::string_view file_data = ImportedTextData(test_file, txt);
	int answer;
	std::sscanf(file_data.data(), "%d", &answer);
	hdk::assert(answer == 42, "Imported text failed. Expected %d, got %d", 42, answer);

	hdk::terminate();
}
