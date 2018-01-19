#define BOOST_TEST_MODULE tpool
#include <boost/test/unit_test.hpp>

#include "tpool.h"

using namespace tasks_pool;

BOOST_AUTO_TEST_CASE( tpool_construction )
{
    BOOST_CHECK_NO_THROW( tpool tp{} )
    BOOST_CHECK_NO_THROW( tpool tp(10) );
    BOOST_CHECK_THROW( tpool tp{0}, std::exception );
}

BOOST_AUTO_TEST_CASE( tpool_get_no_threads )
{
	{
		tpool tp;
		BOOST_CHECK(tp.get_no_threads() == 1);
	}

	{
		tpool tp { 10 };
		BOOST_CHECK(tp.get_no_threads() == 10);
	}

	{
		BOOST_CHECK_THROW(tpool tp{ 0 }, std::exception);
	}
}

BOOST_AUTO_TEST_CASE( tpool_get_no_added_tasks_basic )
{
	{
		tpool tp;
		BOOST_CHECK(tp.get_no_added_tasks() == 0);
	}

	{
		tpool tp;
		tp.add([](){});
		BOOST_CHECK(tp.get_no_added_tasks() == 1);
	}

	{
		tpool tp;
		for (int i = 0; i < 100; i++) {
			BOOST_CHECK(tp.get_no_added_tasks() == i);
			tp.add([](){});
		}
		BOOST_CHECK(tp.get_no_added_tasks() == 100);
	}
}

BOOST_AUTO_TEST_CASE( tpool_wait_for_all_basic )
{
	{
		tpool tp;
		tp.wait_for_all();
	}

	{
		tpool tp;
		tp.add([](){});
		tp.wait_for_all();
	}

	{
		tpool tp;
		for (int i = 0; i < 100; i++) 
			tp.add([](){});
		tp.wait_for_all();
	}

	{
		tpool tp;
		for (int i = 0; i < 100; i++) {
			tp.add([](){});
			tp.wait_for_all();
		}
		tp.wait_for_all();
	}
}

BOOST_AUTO_TEST_CASE( tpool_construction_1_thread_1_task )
{
	tpool tp{};

	tp.wait_for_all();

	tp.add([](){});

	tp.wait_for_all();
}

BOOST_AUTO_TEST_CASE( tpool_construction_1_thread_N_task )
{
	tpool tp;
	for(int i = 0; i < 100; i++)
		tp.add([]() {});

	tp.wait_for_all();
}


