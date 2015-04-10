#ifndef BLP_BASE_COUNT_DOWN_H
#define BLP_BASE_COUNT_DOWN_H

#include "Condition.h"
#include "Mutex_lock.h"

namespace blp
{
class CCountDown
{
public:
	explicit CCountDown(int count);

	void wait();

	void countDown();

	int getCount();
private:
	mutable CMutexLock _mutex;
	CCondition _cond;
	int _count;
};
}

#endif
