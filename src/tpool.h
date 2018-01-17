#pragma once
#include <cstdint>
#include <forward_list>
#include <functional>
#include <vector>
#include <thread>

namespace tpool
{

class tpool final
{
private:
	using list_t = std::forward_list<std::function<void(void)>>;
	using threads_t = std::vector<std::thread>;

public:
	tpool(uint32_t no_threads);
	~tpool();

private:
	uint32_t	no_threads = 1;	// number of threads
	list_t		tasks;			// list of tasks to execute.			
	threads_t	threads;		// work threads

};

} // namespace tpool
