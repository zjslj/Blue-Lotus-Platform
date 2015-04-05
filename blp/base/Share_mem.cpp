//Sharemem.cpp
#include "Share_mem.h"
#include <errno.h>
#include <string.h>
#include "Exception.h"

using namespace blp;

/**
 * 构造函数
 */
CShareMem::CShareMem(key_t key, int iSize, bool autoRemove)
{
	_bFirstCreate = true;
	_bAutoRemove = autoRemove;
	_iShmSize = iSize;

	_iShmId = shmget(key, iSize, IPC_CREAT | IPC_EXCL | 0666);
	if(_iShmId < 0)
	{
		if(errno != EEXIST)
		{
			throw CException(-1, "Create shm mem failed", __FILE__, __LINE__);
		}

		if((_iShmId= shmget(key, iSize, 0666)) < 0)
		{
			throw CException(-1, "Get shm mem failed", __FILE__, __LINE__);
		}
		_bFirstCreate =  false;
	}

	//connect 
	if((_pAddress = shmat(_iShmId, NULL, 0)) == (void*) -1)
	{
		throw CException(-1, "Connect shm mem failed", __FILE__, __LINE__);
	}
	//init
	if(_bFirstCreate)
	{
		memset(_pAddress, 0, iSize);
	}
}

CShareMem::CShareMem(const char* path, int id, int iSize, bool autoRemove)
{
	_bFirstCreate = true;
	_bAutoRemove = autoRemove;
	_iShmSize = iSize;

	key_t iKey = ftok(path, id);

	_iShmId = shmget(iKey, iSize, IPC_CREAT | IPC_EXCL | 0666);
	if(_iShmId < 0)
	{
		if(errno != EEXIST)
		{
			throw CException(-1, "Create shm mem failed", __FILE__, __LINE__);
		}

		if((_iShmId= shmget(iKey, iSize, 0666)) < 0)
		{
			throw CException(-1, "Get shm mem failed", __FILE__, __LINE__);
		}
		_bFirstCreate =  false;
	}

	//connect 
	if((_pAddress = shmat(_iShmId, NULL, 0)) == (void*) -1)
	{
		throw CException(-1, "Connect shm mem failed", __FILE__, __LINE__);
	}
	//init
	if(_bFirstCreate)
	{
		memset(_pAddress, 0, iSize);
	}	
}

/**
 * 析构函数
 */
CShareMem::~CShareMem()
{
	shmdt(_pAddress);
	if(_bAutoRemove)
	{
		struct shmid_ds statInfo;
		if(shmctl(_iShmId, IPC_STAT, &statInfo) == 0)
		{
			if(statInfo.shm_nattch == 0)
			{
				shmctl(_iShmSize, IPC_RMID, NULL);
			}
		}
	}
}

void* CShareMem::address()
{
	return _pAddress;
}

int CShareMem::shmId()
{
	return _iShmId;
}

int CShareMem::shmSize()
{
	return _iShmSize;
}

bool CShareMem::isFirstCreate()
{
	return _bFirstCreate;
}
