#include <iostream>
#include "thread.h"

using namespace std;
int main(int argc, char **argv)
{
	bool ret;
	MutiThread *mt = new MutiThread();
	ret = mt->start();
	mt->join(6000);
	while(1)
	{
		cout << "this is main thread" << endl;
		sleep(2);
	}
	return 0;
}


