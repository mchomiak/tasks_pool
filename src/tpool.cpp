#include <iostream>
#include <cstdint>
#include <exception>

#include "tpool.h"

using namespace std;

namespace tasks_pool
{
	std::mutex tpool::next_task_m;
	std::condition_variable	tpool::next_task_cv;
	std::condition_variable	tpool::task_done_cv;

	tpool::tpool(uint32_t no_threads)
		:	threads(no_threads)
	{
		if (no_threads == 0)
			throw std::runtime_error("Number of worker threads can't be 0!");

		for (auto& t : threads) {
			t = thread(std::bind(tpool::thread_f, ref(*this)));
			std::this_thread::sleep_for(50ms);
		}
		
		cout << "number of threads created: " << threads.size() << endl;
	}

tpool::~tpool()
{
	cout << "!!!!!!!!!!!!!!!! tpool::~tpool()" << endl;
	{
		std::lock_guard<std::mutex> guard(tpool::next_task_m);
		finishing = true;
		tpool::next_task_cv.notify_all();
	}
	for (auto& t : threads)
		t.join();
	cout << "!!!!!!!!!!!!!!!! tpool::~tpool() end" << endl;
}

void tpool::add(task_t t)
{
	{
		std::lock_guard<std::mutex> guard(tpool::next_task_m);
		tasks.push_back(t);
	}
	tpool::next_task_cv.notify_one();
	++no_tasks_added;
	cout << "Added new task. Number of tasks in queue: " << tasks.size() << endl;
}

void tpool::wait_for_all()
{
	cerr << "waiting for all" << endl;
	while (true) {
		std::unique_lock<std::mutex> guard(tpool::next_task_m);
		tpool::task_done_cv.wait(guard);
		if (tasks.size() == 0 && in_progress == 0)
			break;
	}
	cerr << "waiting for all done!" << endl;
}

void tpool::thread_f(tpool& tp)
{
	static int n = 0;
	int id = n++;
	while (true) {
		tpool::task_t task;
		{
			//waiting for a signal from tpool
			std::unique_lock<std::mutex> ul(tpool::next_task_m);
			if (tp.tasks.size() > 0) {
				task = tp.tasks.front();
				tp.tasks.pop_front();
				tp.in_progress++;
			}
			else if (!tp.finishing) {
				tpool::next_task_cv.wait(ul);
				if (tp.tasks.size() > 0) {
					task = tp.tasks.front();
					tp.tasks.pop_front();
					tp.in_progress++;
				}
			}
		}
		if (task)
		{
			task();
			std::unique_lock<std::mutex> ul(tpool::next_task_m);
			tp.in_progress--;
			tpool::task_done_cv.notify_all();
		}
		else
			break;
	}
}

} //namespace tpool
