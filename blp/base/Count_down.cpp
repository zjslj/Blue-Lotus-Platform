#include "Count_down.h"

using namespace blp;

CCountDown::CCountDown(int count)
	: _mutex(), _cond(_mutex), _count(count)
{

}

void CCountDown::wait()
{
	CMutexLockGuard lock(_mutex);
	while(_count > 0)
	{
		_cond.wait();
	}
}

void CCountDown::countDown()
{
	CMutexLockGuard lock(_mutex);
	--_count;
	if(_count == 0)
	{
		_cond.notifyAll();
	}
}

int CCountDown::getCount()
{
	CMutexLockGuard lock(_mutex);
	return _count;
}