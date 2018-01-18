#include <iostream>
#include <chrono>
#include <thread>
#include "tpool.h"

using namespace std;
using namespace tasks_pool;

int main(int arc, char** argv)
{
	cout << "Hello" << endl;

	{
		tpool tp{ 3 };

		for (int i = 0; i < 10; i++)
			tp.add([=]() {
			cerr << "    starting " << i << "..." << endl;
			srand(time(nullptr));
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
			cerr << "    finishing " << i << "." << endl;
		});
		tp.wait_for_all();
	}

	cout << "This is the end!" << endl;
	return 0;
}
 
