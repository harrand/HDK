#include "hdk/hdk.hpp"
#include "hdk/macros.hpp"
#include "hdk/debug.hpp"
#include <cstdio>

#include ImportedTextHeader(test_file, txt)

int main()
{
	hdk::initialise();
	
	int answer;
	std::sscanf(ImportedTextData(test_file, txt).data(), "%d", &answer);
	hdk::assert(answer == 42, "Imported text failed. Expected %d, got %d", 42, answer);

	hdk::terminate();
}
