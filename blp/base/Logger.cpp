// 使用方法：
// 1) 构造一个CLogger对象
//    CLogger logger(".", "test.log", 1024*1024, 10);
// 2) 调用print方法写日志
//    logger.info(__FILE__, __LINE__, "%s\n", "test");

#include "Logger.h"

using namespace blp;

CLogger::CLogger(
                     const std::string& log_dir,
                     const std::string& filename,
                     uint32_t log_size,
                     uint8_t log_numer,
                     time_t roll_interval,
                     uint16_t record_size)
     : _fd(-1),
       _log_dir(log_dir),
       _filename(filename),
       _log_size(log_size),
       _log_numer(log_numer),
       _roll_interval(roll_interval),
       _record_size(record_size),
       _last_roll_time(0),
       _roll_type(0)
{
	//_file_stamp
	char timebuf[32];
    struct tm tm;
    time_t now = time(NULL);
    localtime_r(&now, &tm);
	
	if(roll_interval >= 86400)
	{
		strftime(timebuf, sizeof timebuf, "%Y%m%d", &tm);		
	}
    else
    {
		strftime(timebuf, sizeof timebuf, "%Y%m%d-%H%M", &tm);
	}
	_last_roll_time = now;
	_file_stamp = timebuf;

	_log_filepath = log_dir + std::string("/") + filename + "_" + _file_stamp + ".log";
    
    _fd = open(_log_filepath.c_str(), O_WRONLY|O_CREAT|O_APPEND, DATA_FILE_MODE_DEFAULT);

    if (_fd != -1)
    {
        if (_log_size < 1024)
        {
            _log_size = 1024;
        }

        if (_record_size < 1024)
        {
            _record_size = 1024;
        }
		if(_roll_interval > 86400)
		{
			_roll_interval = 86400;
		}
		if(_roll_interval < 60)
		{
			_roll_interval = 60;
		}
    }
}

 CLogger::~CLogger()
{
    if (_fd != -1)
        close(_fd);
}

 bool CLogger::is_ok() const
{
    return _fd != -1;
}

 void CLogger::raw(const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(NULL, 0, NULL, format, ap);
        va_end(ap);
    }
}

 void CLogger::debug(const char* file, int line, const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(file, line, "DEBUG", format, ap);
        va_end(ap);
    }
}

 void CLogger::info(const char* file, int line, const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(file, line, "INFO", format, ap);
        va_end(ap);
    }
}

 void CLogger::error(const char* file, int line, const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(file, line, "ERROR", format, ap);
        va_end(ap);
    }
}

 void CLogger::warning(const char* file, int line, const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(file, line, "WARNING", format, ap);
        va_end(ap);
    }
}

 void CLogger::fatal(const char* file, int line, const char* format, ...)
{
    if (_fd != -1)
    {
        va_list ap;
        va_start(ap, format);

        print(file, line, "FATAL", format, ap);
        va_end(ap);
    }
}

 const std::string& CLogger::get_log_filepath() const
{
    return _log_filepath;
}

 bool CLogger::enabled_debug() const
{
    return true;
}

 bool CLogger::enabled_info() const
{
    return true;
}

 bool CLogger::enabled_error() const
{
    return true;
}

 bool CLogger::enabled_warning() const
{
    return true;
}

 bool CLogger::enabled_fetal() const
{
    return true;
}

// 格式：[YYYY-MM-DD hh:mm:ss][pid][Level][tag][file:line]log，其中tag是可选的
 void CLogger::print(const char* file, int line, const char* level, const char* format, va_list& ap)
{    
    if (_fd != -1)
    {
        std::string log_header; // 存储每条日志头

        // raw日志，不加头
        if (level != NULL)
        {
            // date&time
            char timebuf[32];
            struct tm tm;
            time_t now = time(NULL);
            localtime_r(&now, &tm); 
            strftime(timebuf, sizeof timebuf, "%Y%m%d-%H%M%S", &tm);
            log_header = std::string("[") + std::string(timebuf) + std::string("]");
            // level
            log_header += std::string("[") + std::string(level) + std::string("]");
            // pid
            log_header += std::string("[") + CUtils::int_tostring(getpid()) + std::string("]");

            if (!_tag1.empty()) // tag1
            {
                log_header += std::string("[") + _tag1 + std::string("]");
            }
            if (!_tag2.empty()) // tag2
            {
                log_header += std::string("[") + _tag2 + std::string("]");
            }
            if (file != NULL) // file&line
            {
                log_header += std::string("[") +
                              std::string(file) + std::string(":") + CUtils::int_tostring(line) +
                              std::string("]");
            }
        }

        // 自动添加换行符，所以加1
        size_t content_size = _record_size - log_header.size() + 1;
        CScopedArray<char> content_buffer(new char[content_size]);

        // writev参数
        struct iovec iov[2];

        // log header
        iov[0].iov_base = const_cast<char*>(log_header.data());
        iov[0].iov_len = log_header.size(); // 不含结尾符

        // log content
        iov[1].iov_base = content_buffer.get();
        iov[1].iov_len = CUtils::fix_vsnprintf(content_buffer.get(), content_size, format, ap);
        content_buffer.get()[iov[1].iov_len - 1] = '\n'; // 添加换行符

        // 写入文件
        ssize_t bytes_writed = writev(_fd, iov, sizeof(iov)/sizeof(iov[0]));
        if (bytes_writed > 0)
        {
            // 滚动处理，目前根据大小滚动，修改支持根据时间来滚动
            if (need_rotate())
            {
                std::string lock_path = _log_dir + std::string("/.") + _filename + std::string(".lock");
                CFileLocker file_locker(lock_path.c_str());

                // 需要再次判断，原因是可能其它进程已处理过了
                openfile();
                if (need_rotate())
                {
                    rotate_log();
                }
            }
        }
    }
}

 bool CLogger::need_rotate()
{
	//如果滚动是时间方式，则根据时间来滚动，同时考虑大小
	bool bRet = false;
	bRet = CUtils::get_file_modify_time(_fd) - _last_roll_time > _roll_interval;
	if(!bRet)
	{
		bRet = CUtils::get_filesize(_fd) > static_cast<int64_t>(_log_size);
		if(bRet) _roll_type = 0;
	}
	else
	{
		_roll_type = 1;
	}

	
    return bRet;
}

 void CLogger::rotate_log()
{
	//如果是时间切换，则需要更新时间戳，使用新文件，如果是大小切换，则需要rename
	if(1 == _roll_type)
	{
		//根据时间切换，则不重命名之前的文件，而是打开新的时间文件
		reset();
		//获取新的还有时间格式的文件名字
		char timebuf[32];
	    struct tm tm;
	    time_t now = time(NULL);
	    localtime_r(&now, &tm); 
		if(_roll_interval >= 86400)
		{
			strftime(timebuf, sizeof timebuf, "%Y%m%d", &tm);
		}
		else
		{
			strftime(timebuf, sizeof timebuf, "%Y%m%d-%H%M", &tm);
		}
	    
		_file_stamp = timebuf;
		_last_roll_time = now;
		std::string new_file_name = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log";
		_fd = open(new_file_name.c_str(), O_WRONLY|O_CREAT|O_EXCL, DATA_FILE_MODE_DEFAULT);
	}
	else
	{
		//根据文件大小切换，则重命名之前的文件
		std::string new_path;  // 滚动后的文件路径，包含目录和文件名
	    std::string old_path;  // 滚动前的文件路径，包含目录和文件名
	    
	    // 轮回，一切重新开始
	    reset();

	    // 历史滚动
	    for (int8_t i=_log_numer-1; i>0; --i)
	    {
	        new_path = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log" + std::string(".") + CUtils::int_tostring(i);
	        old_path = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log" + std::string(".") + CUtils::int_tostring(i-1);

	        if (0 == access(old_path.c_str(), F_OK))
	        {
	            rename(old_path.c_str(), new_path.c_str());
	        }
	    }

	    if (_log_numer > 0)
	    {
	        // 当前滚动
	        new_path = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log" + std::string(".1");
	        old_path = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log";
	        if (0 == access(old_path.c_str(), F_OK))
	        {
	            rename(old_path.c_str(), new_path.c_str());
	        }
	    }

	    // 重新创建
	    _fd = open(old_path.c_str(), O_WRONLY|O_CREAT|O_EXCL, DATA_FILE_MODE_DEFAULT);
	}
    
}

 void CLogger::reset()
{
    if (_fd != -1)
    {
        close(_fd);
        _fd = -1;
    }
}

 void CLogger::openfile()
{
	reset();
	std::string file = _log_dir + std::string("/") + _filename + "_" + _file_stamp + ".log";;

	_fd = open(file .c_str(), O_WRONLY|O_CREAT|O_APPEND, DATA_FILE_MODE_DEFAULT);
}

 void CLogger::set_file_name(std::string file_name)
{
	if(_roll_type == 2)
	{
		//file_name 增加时间
		
	}
	else
	{
		_filename = file_name;
	}
}


template <typename IntType>
 void CLogger::set_tag1(IntType tag)
{
    _tag1 = CStringUtil::any2string(tag);
}

 void CLogger::set_tag1(const std::string& tag)
{
    _tag1 = tag;
}

template <typename IntType>
 void CLogger::set_tag2(IntType tag)
{
    _tag2 = CStringUtil::any2string(tag);
}

 void CLogger::set_tag2(const std::string& tag)
{
    _tag2 = tag;
}




