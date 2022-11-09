#include "hdk/debug.hpp"
#include "debugbreak.h"

namespace hdk
{
	void debug_break()
	{
		::debug_break();
	}
}
