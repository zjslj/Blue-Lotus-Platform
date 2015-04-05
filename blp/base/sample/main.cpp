#include <iostream>
#include "inc.h"
using namespace std;
using namespace blp;

int main()
{
	cout << "main test" << endl;
	/*
	CLogger* logger = new CLogger(".", "test", 102400, 10, 60);

	AtomicInt64 ato;
	DEBUG(logger, "get=[%ld]", ato.get());
	DEBUG(logger, "addAndGet=[%ld]", ato.addAndGet(5));
	DEBUG(logger, "getAndAdd=[%ld]", ato.getAndAdd(5));
	DEBUG(logger, "get=[%ld]", ato.get());
	DEBUG(logger, "getAndSet=[%ld]", ato.getAndSet(12));
	DEBUG(logger, "get=[%ld]", ato.get());

	//创建一块共享内存，写入数据
	CShareMem shm((key_t)123456, 10000, true);	
	while(false)
	{
		string str = "test\n";
		strncpy((char*)shm.address(), str.c_str(), str.size());
		
		//printf("string :%s\n",(char*)shm.address()); 
		sleep(1);
	}
	*/
	stringUtilTest();

	timeUtilTest();
	return 0;
}