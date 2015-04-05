//共享内存操作
#ifndef BLP_BASE_SHARE_MEM_H
#define BLP_BASE_SHARE_MEM_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace blp
{
class CShareMem
{
public:
	/**
	 * 构造函数
	 */
	CShareMem(key_t key, int iSize, bool autoRemove=false);
	CShareMem(const char* path, int id, int iSize, bool autoRemove=false);
	/**
	 * 析构函数
	 */
	~CShareMem();

	void* address();

	int shmId();

	int shmSize();

	bool isFirstCreate();
private:
	int _iShmId;
	int _iShmSize;
	int _bFirstCreate;
	bool _bAutoRemove;
	void* _pAddress;
};
}

#endif

