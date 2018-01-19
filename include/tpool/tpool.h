#pragma once
#include <cstdint>
#include <list>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace tasks_pool
{

class tpool final
{
// types
public:
	using task_t = std::function<void(void)>;
private:
	using tasks_t = std::list<task_t>;
	using threads_t = std::vector<std::thread>;

// constructors
public:
	tpool(uint32_t no_threads = 1);
	~tpool();

// methods
public:
	/** Add new task to the queue
	*/
	void		add(task_t t);

	/* returns the number of working threads
	*/
	uint32_t	get_no_threads() const noexcept		{ return threads.size(); }

	/* returns the number of tasks added to the queue
	*/
	uint64_t	get_no_added_tasks() const noexcept	{ return no_tasks_added; }

	/* waits for all the tasks to be executed
	*/
	void		wait_for_all();

// fields
private:
	tasks_t							tasks;				// list of tasks to execute
	std::atomic<std::uint64_t>		no_tasks_added{0};	// number of tasks added to the queue
	std::mutex						tasks_guard;		// mutex to guard operations of tasks list
	std::atomic<std::uint32_t>		in_progress{0};	// number of tasks in progress

	threads_t						threads;			// work threads
	bool							finishing = false;

// statics
private:
	static void thread_f(tpool& tp);

// static fields
private:
	static std::mutex		next_task_m;
	static std::condition_variable	next_task_cv;
	static std::condition_variable	task_done_cv;
};

} // namespace tpool
