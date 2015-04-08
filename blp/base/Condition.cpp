#include "Condition.h"
#include <errno.h>

using namespace blp;

bool CCondition::waitForSeconds(int sec)
{
  struct timespec abstime;
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += sec;
  CMutexLock::CUnassignGuard ug(_mutex);
  return ETIMEDOUT == pthread_cond_timedwait(&_pcond, _mutex.getPthreadMutex(), &abstime);
}