#include <cstdint>
#include <exception>

#include "tpool.h"

using namespace std;

namespace tpool
{


tpool::tpool(uint32_t no_threads)
	:	no_threads(no_threads)
{
	if (no_threads == 0)
		throw std::exception("Number of threads can't be 0");
}

tpool::~tpool()
{
}

} //namespace tpool
