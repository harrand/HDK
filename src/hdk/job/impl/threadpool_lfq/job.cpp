#include "hdk/job/impl/threadpool_lfq/job.hpp"
#include "hdk/debug.hpp"
#include "hdk/profile.hpp"
#include <chrono>
#include <limits>

namespace hdk::impl
{
	constexpr std::size_t job_id_null = std::numeric_limits<std::size_t>::max();

	job_system_threadpool_lfq::job_system_threadpool_lfq()
	{
		HDK_PROFZONE("job_system_threadpool_lfq()", 0xFFAA0000);
		for(std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
		{
			this->thread_pool.emplace_back
			(
				std::thread([this, i](){this->tmain(i);}),
				i,
				job_id_null
			);
		}
	}
	
	job_system_threadpool_lfq::~job_system_threadpool_lfq()
	{
		HDK_PROFZONE("~job_system_threadpool_lfq()", 0xFFAA0000);
		this->requires_exit = true;
		for(worker_t& worker : this->thread_pool)
		{
			worker.thread.join();
		}
		hdk::assert(!this->any_work_remaining());
	}

	job_handle job_system_threadpool_lfq::execute(job_t job)
	{
		HDK_PROFZONE("job_system_threadpool_lfq::execute(job_t)", 0xFFAA0000);
		job_info_t jinfo
		{
			.func = job,
			.id = this->lifetime_count.load()
		};
		{
			std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
			this->waiting_job_ids.push_back(this->lifetime_count);
		}
		this->jobs.enqueue(jinfo);
		return static_cast<hanval>(this->lifetime_count++);
	}

	void job_system_threadpool_lfq::block(job_handle j) const
	{
		HDK_PROFZONE("job_system_threadpool_lfq::block(job_handle)", 0xFFAA0000);
		while(!this->complete(j))
		{
			job_system_threadpool_lfq::wait_a_bit();
		}
	}

	bool job_system_threadpool_lfq::complete(job_handle j) const
	{
		std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
		return std::find(this->waiting_job_ids.begin(), this->waiting_job_ids.end(), static_cast<std::size_t>(static_cast<hanval>(j))) == this->waiting_job_ids.end() && std::all_of(this->thread_pool.begin(), this->thread_pool.end(), [jid = static_cast<std::size_t>(static_cast<hanval>(j))](const worker_t& worker){return worker.current_job != jid;});
	}

	bool job_system_threadpool_lfq::any_work_remaining() const
	{
		std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
		return !this->waiting_job_ids.empty() || this->size() > 0 || std::any_of(this->thread_pool.begin(), this->thread_pool.end(), [](const worker_t& worker){return worker.current_job != job_id_null;});
	}

	void job_system_threadpool_lfq::block_all() const
	{
		HDK_PROFZONE("job_system_threadpool_lfq::block_all()", 0xFFAA0000);
		while(this->any_work_remaining())
		{
			job_system_threadpool_lfq::wait_a_bit();
		}
	}

	unsigned int job_system_threadpool_lfq::size() const
	{
		return this->jobs.size_approx();
	}

	void job_system_threadpool_lfq::tmain(std::size_t local_tid)
	{
		HDK_THREAD("hdk::job_system() Worker");
		worker_t& worker = this->thread_pool[local_tid];
		while(!this->requires_exit.load())
		{
			job_info_t job;
			bool found = this->jobs.try_dequeue(job);
			if(!found)
			{
				this->wait_a_bit();
				continue;
			}

			worker.current_job = job.id;
			HDK_PROFZONE("job thread - do job", 0xFFAAAA00);
			{
				std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
				auto iter = std::find(this->waiting_job_ids.begin(), this->waiting_job_ids.end(), job.id);
				hdk::assert(iter != this->waiting_job_ids.end(), "Job system thread took a job, but it's id is not on the list of waiting jobs, as it should be.");
				this->waiting_job_ids.erase(iter);
			}
			job.func();
			worker.current_job = job_id_null;
		}
	}
	
	void job_system_threadpool_lfq::wait_a_bit()
	{
		std::this_thread::sleep_for(std::chrono::duration<int, std::micro>(10));
	}
}
