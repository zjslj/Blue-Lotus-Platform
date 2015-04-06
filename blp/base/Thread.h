#ifndef _BLP_BASE_THREAD_H
#define _BLP_BASE_THREAD_H

#include "Atomic.h"
#include "Scoped_ptr.h"
#include <string>
#include <pthread.h>

namespace blp{
class CThread{
	typedef void (*ThreadFunc) ();
public:
	explicit CThread(const ThreadFunc func, const std::string& name = string());
	~CThread();

	void start();
	int join();

	bool started() const {return _started;}
	pid_t tid() const {return *_tid;}
	const std::string name() const {return _name;}

	static int count() {return _count.get();}
private:
  	void setDefaultName();

	bool _started;
	bool _joined;
	pthread_t _pthreadId;
	std::string _name;
	CScopedPtr<pid_t> _tid;
	ThreadFunc _func;

	static AtomicInt32 _count;
};
}
#endif