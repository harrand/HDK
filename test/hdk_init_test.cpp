#include "hdk/hdk.hpp"
#include "hdk/data/version.hpp"
#include "hdk/debug.hpp"

int main()
{
	hdk::initialise();
	hdk::report("HDK v%s", hdk::get_version().to_string().c_str());
	hdk::terminate();
}
