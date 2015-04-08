//Mutex_lock.h
#ifndef _BLP_BASE_MUTEX_LOCK_H
#define _BLP_BASE_MUTEX_LOCK_H

#include <pthread.h>

namespace blp
{
class CMutexLock
{
public:
	CMutexLock()
		:_holder(0)
	{
		pthread_mutex_init(&_mutex, NULL);
	}
	~CMutexLock()
	{
		if(_holder == 0)
		{
			pthread_mutex_destroy(&_mutex);
		}
	}
	void lock()
	{
		pthread_mutex_lock(&_mutex);
		assignHolder();
	}

	void unlock()
	{
		unassignHolder();
		pthread_mutex_unlock(&_mutex);
	}

	pthread_mutex_t* getPthreadMutex() /* non-const */
	{
		return &_mutex;
	}
private:
	friend class CCondition;
	class CUnassignGuard
	{
	public:
		CUnassignGuard(CMutexLock& owner)
			: _owner(owner)
		{
			_owner.unassignHolder();
		}

		~CUnassignGuard()
		{
			_owner.assignHolder();
		}

	private:
		CMutexLock& _owner;
	};

	void unassignHolder()
	{
		_holder = 0;
	}

	void assignHolder()
	{
		//_holder = CurrentThread::tid();
	}

	pthread_mutex_t _mutex;
	pid_t _holder;
};

class CMutexLockGuard
{
public:
	explicit CMutexLockGuard(CMutexLock& mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~CMutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	CMutexLock& _mutex;
};
}
#endif
