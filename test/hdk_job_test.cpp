#include "hdk/hdk.hpp"
#include "hdk/job/job.hpp"
#include "hdk/debug.hpp"
#include <numeric>
#include <array>
#include <algorithm>

#define TESTFUNC_BEGIN(n) void n(){hdk::assert(!hdk::job_system().any_work_remaining());
#define TESTFUNC_END ;hdk::job_system().block_all(); hdk::assert(!hdk::job_system().any_work_remaining());}

TESTFUNC_BEGIN(basic_job)
	int x = 1;
	auto j = hdk::job_system().execute([&x]()
	{
		x += 5;
	});
	hdk::job_system().block(j);
	hdk::assert(hdk::job_system().complete(j));
	hdk::assert(!hdk::job_system().any_work_remaining());
	hdk::assert(x == 6, "Expected value to be %d but it is %d", 6, x);
TESTFUNC_END

TESTFUNC_BEGIN(job_reuse)
	auto j = hdk::job_system().execute([](){});
	hdk::job_system().block_all();
	hdk::assert(hdk::job_system().complete(j));
	auto k = hdk::job_system().execute([](){});
	//hdk::assert(j == k, "Old job is not being re-used.");
TESTFUNC_END

TESTFUNC_BEGIN(multi_job)
	constexpr std::size_t job_size = 64;
	constexpr std::size_t job_chunk_length = 8;
	std::array<int, job_size> x;
	std::iota(x.begin(), x.end(), 0);
	std::array<int, job_size> y;
	std::iota(y.rbegin(), y.rend(), 0);
	
	std::array<int, job_size> z;
	std::fill_n(z.begin(), job_size, 0);

	for(std::size_t i = 0; i < job_size; i += (job_size/job_chunk_length))
	{
		hdk::job_system().execute([begin = i, end = i + job_chunk_length, &x, &y, &z]()
		{
			for(std::size_t j = begin; j < end; j++)
			{
				z[j] = x[j] + y[j];
			}
		});
	}
	hdk::job_system().block_all();

	hdk::assert(std::all_of(z.begin(), z.end(), [job_size](int x){return x == job_size-1;}), "Multi job did not have expected output. Expected all elements of `z` to be %zu but %zu are", job_size, std::count_if(z.begin(), z.end(), [job_size](int x){return x == job_size-1;}));
TESTFUNC_END

int main()
{
	hdk::initialise();

	for(std::size_t i = 0; i < 256; i++)
	{
		basic_job();
		job_reuse();
		multi_job();
	}

	hdk::terminate();
	return 0;
}
