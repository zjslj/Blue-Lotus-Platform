//Thread.cpp
#include "Thread.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include "Atomic.h"

using namespace blp;

AtomicInt32 CThread::_count;

CThread::CThread(const ThreadFunc func, const std::string& name)
	:_started(false), _joined(false), _pthreadId(0), _name(name), 
	_tid(), _func(func)	
{

}

CThread::~CThread()
{
	if (_started && !_joined)
	{
		pthread_detach(_pthreadId);
	}
}

void CThread::start() throw (CException)
{
	if(_started)
	{
		throw CException(-1, "Thread already started!", __FILE__, __LINE__);
	}

	_started = true;
	if (pthread_create(&_pthreadId, NULL, _func, NULL))
	{
		_started = false;
	}
}

int CThread::join() throw (CException)
{
	if(!_started || _joined)
	{
		throw CException(-1, "Thread not started or already joined!", __FILE__, __LINE__);
	}
	_joined = true;
  	return pthread_join(_pthreadId, NULL);
}

void CThread::setDefaultName()
{
  int count = _count.incrementAndGet();
  if (_name.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", count);
    _name = buf;
  }
}
