#ifndef BLP_BASE_FILE_LOCKER_H
#define BLP_BASE_FILE_LOCKER_H
#include "Config.h"
#include <errno.h>
#include <stdio.h>
#include <string>
#include <sys/file.h>
#include <unistd.h>
namespace blp {

// FileLocker 普通文件锁，总是锁定整个文件
// ExFileLocker 增强型文件锁，可只锁定文件指定部分
// ExclusiveFileLocker 独占普通文件锁
// SharedFileLocker 共享普通文件锁

/**
 * 普通文件锁，总是锁定整个文件，支持独占和共享两种类型，由参数exclusive决定
 * 进程退出时，它所持有的锁会被自动释放
 * 注意同一个FileLocker对象，不要跨线程使用，同一个FileLocker对象总是只会被同一个线程调度
 */
class CFileLocker
{
public:
    /***
     * 不加锁构造函数，由调用者决定何时加锁
     */
    explicit CFileLocker(const char* filepath)
        : _fd(-1), _filepath(filepath)
    {
    }

    /***
     * 自动加锁构造函数
     * ，建议使用SharedFileLocker或ExclusiveFileLocker，替代此构造函数调用
     * @exclusive 是否独占锁
     */
    explicit CFileLocker(const char* filepath, bool exclusive)
        : _fd(-1), _filepath(filepath)
    {
        lock(exclusive);
    }

    ~CFileLocker()
    {
        unlock();
    }

    /**
     * 加锁
     * @exclusive 是否独占锁
     */
    bool lock(bool exclusive)
    {
        // 独占还是共享
        int operation = exclusive? LOCK_EX: LOCK_SH;

        _fd = open(_filepath.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if (_fd != -1)
        {
            if (-1 == flock(_fd, operation))
            {
                int errcode = errno; // Keep
                close(_fd); // 无write动作，不用判断close()的返回值

                _fd = -1;
                errno = errcode; // 恢复，目的是让上层调用者可以使用errno
            }
        }

        return _fd != -1;
    }

    bool unlock()
    {
        bool ret = false;

        if (is_locked())
        {
            if (0 == flock(_fd, LOCK_UN))
                ret = true;

            close(_fd);
        }

        return ret;
    }

    bool is_locked() const
    {
        return _fd != -1;
    }

    operator bool () const
    {
        return _fd != -1;
    }

    /***
     * 返回锁文件路径
     */
    const std::string& get_filepath() const
    {
        return _filepath;
    }

private:
    int _fd;
    std::string _filepath;
};

/**
 * 普通独占文件锁
 */
class CExclusiveFileLocker: public CFileLocker
{
public:
    explicit CExclusiveFileLocker(const char* filepath)
        : CFileLocker(filepath, true)
    {
    }

private:
    bool lock();
    bool unlock();
};

/**
 * 普通共享文件锁
 */
class CSharedFileLocker: public CFileLocker
{
public:
    explicit CSharedFileLocker(const char* filepath)
        : CFileLocker(filepath, false)
    {
    }

private:
    bool lock();
    bool unlock();
};

}
#endif
