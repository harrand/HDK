#include "hdk/job/impl/threadpool_lfq/job.hpp"
#include <chrono>
#include <limits>

namespace hdk::impl
{
	constexpr std::size_t job_id_null = std::numeric_limits<std::size_t>::max();

	job_system_threadpool_lfq::job_system_threadpool_lfq()
	{
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
		this->requires_exit = true;
		for(worker_t& worker : this->thread_pool)
		{
			worker.thread.join();
		}
	}

	job_handle job_system_threadpool_lfq::execute(job_t job)
	{
		job_info_t jinfo
		{
			.state = job_info_t::job_state::created,
			.func = job,
			.id = this->lifetime_count
		};
		this->waiting_job_ids.push_back(this->lifetime_count);
		this->jobs.enqueue(jinfo);
		return static_cast<hanval>(this->lifetime_count++);
	}

	void job_system_threadpool_lfq::block(job_handle j) const
	{
		while(!this->complete(j))
		{
			job_system_threadpool_lfq::wait_a_bit();
		}
	}

	bool job_system_threadpool_lfq::complete(job_handle j) const
	{
		for(const worker_t& worker : this->thread_pool)
		{
			if(worker.current_job.load() == static_cast<std::size_t>(static_cast<hanval>(j)))
			{
				return false;
			}
		}
		std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
		return std::find(this->waiting_job_ids.begin(), this->waiting_job_ids.end(), static_cast<std::size_t>(static_cast<hanval>(j))) == this->waiting_job_ids.end();
	}

	bool job_system_threadpool_lfq::any_work_remaining() const
	{
		return this->size() > 0;
	}

	void job_system_threadpool_lfq::block_all() const
	{
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
		worker_t& worker = this->thread_pool[local_tid];
		while(!this->requires_exit.load())
		{
			job_info_t job;
			bool found = this->jobs.try_dequeue(job);
			if(!found)
			{
				std::this_thread::sleep_for(std::chrono::duration<unsigned int, std::milli>(1));
				continue;
			}

			worker.current_job = job.id;
			{
				std::unique_lock<std::mutex> lock(this->waiting_job_id_mutex);
				this->waiting_job_ids.erase(std::remove(this->waiting_job_ids.begin(), this->waiting_job_ids.end(), job.id));
			}
			job.state = job_info_t::job_state::running;
			job.func();
			job.state = job_info_t::job_state::finished;
			worker.current_job = job_id_null;
		}
	}
	
	void job_system_threadpool_lfq::wait_a_bit()
	{
		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));
	}
}
