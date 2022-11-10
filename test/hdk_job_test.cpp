#include "hdk/hdk.hpp"
#include "hdk/debug.hpp"
#include "hdk/job/job.hpp"

int main()
{
	hdk::initialise();

	int x = 1;
	auto j = hdk::job_system().execute([&x]()
	{
		x += 5;
	});
	hdk::job_system().block(j);
	hdk::assert(hdk::job_system().complete(j));
	hdk::assert(!hdk::job_system().any_work_remaining());
	hdk::assert(x == 6, "Expected value to be %d but it is %d", 6, x);

	hdk::terminate();
	return 0;
}
