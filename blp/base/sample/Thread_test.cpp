//Thread_test.cpp

#include "inc.h"
#include "Thread.h"
#include <iostream>

using namespace blp;
using namespace std;

void* threadPrint(void * para)
{
    cout << "threadPrint==>" << endl;
    return NULL;
}

void threadTest()
{
	CThread oThread(&threadPrint, "zjslj");
	oThread.start();
    cout << oThread.name() << endl;
    cout << CThread::count() << endl;
    cout << oThread.started() << endl;
    try
    {
    	oThread.start();
    }
    catch(CException& ex)
    {
    	cout << "started   === errCode:" << ex.error() << ", errMsg:" << ex.what() << endl;
    }
    oThread.join();
    cout << "----" << oThread.count() << endl; 

}
