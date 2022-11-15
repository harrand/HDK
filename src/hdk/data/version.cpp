#include "hdk/data/version.hpp"

namespace hdk
{
	version get_version()
	{
		return version::from_binary_string(HDK_VER);
	}
}
