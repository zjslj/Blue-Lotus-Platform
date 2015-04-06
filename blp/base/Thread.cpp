//Thread.cpp
#include "Thread.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

using namespace blp;

AtomicInt32 CThread::_count ＝ 0；
CThread::CThread(const ThreadFunc func, const std::string& name)
	:_started(false), _joined(false), _pthreadId(0), _name(name), 
	_tid(), _func(func), 	
{

}

CThread::~CThread()
{
	if (_started && !_joined)
	{
		pthread_detach(_pthreadId);
	}
}

void CThread::start()
{
	_started = true;
	detail::ThreadData* data = new detail::ThreadData(func_, name_, tid_);
	if (pthread_create(&_pthreadId, NULL, &detail::startThread, data))
	{
		_started = false;
		delete data; 
	}
}

int CThread::join()
{

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
