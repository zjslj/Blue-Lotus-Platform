#ifndef BLP_BASE_CONDITION_H
#define BLP_BASE_CONDITION_H

#include "Mutex_lock.h"
#include <pthread.h>

namespace blp
{
class CCondition
{
public:
	explicit CCondition(CMutexLock& mutex)
		: _mutex(mutex)
	{
		pthread_cond_init(&_pcond, NULL);
	}
	~CCondition()
	{
		pthread_cond_destroy(&_pcond);
	}

	void wait()
	{
		CMutexLock::CUnassignGuard ug(_mutex);
		pthread_cond_wait(&_pcond, _mutex.getPthreadMutex());
	}
	bool waitForSeconds(int sec);
	void notify()
	{
		pthread_cond_signal(&_pcond);
	}

	void notifyAll()
	{
		pthread_cond_broadcast(&_pcond);
	}

private:
	CMutexLock& _mutex;
	pthread_cond_t _pcond;

};
}
#endif