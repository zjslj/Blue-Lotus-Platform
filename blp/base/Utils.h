#ifndef BLP_UTIL_H
#define BLP_UTIL_H

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string>
#include <time.h>
#include <math.h>
#include <sstream>
#include "Config.h"

namespace blp{

class CUtils
{
public:

	static  int64_t get_filesize(int fd);

	static time_t get_file_modify_time(int fd);

	static std::string int_tostring(int16_t source);

    static std::string int_tostring(int32_t source);

    static std::string int_tostring(int64_t source);

    static std::string int_tostring(uint16_t source);

    static std::string int_tostring(uint32_t source);

    static std::string int_tostring(uint64_t source);
    
    static int fix_vsnprintf(char *str, size_t size, const char *format, va_list ap);


    /***
      * delete帮助类，用来自动释放new分配的内存
      */
    template <class ObjectType>
    class DeleteHelper
    {
    public:
        /***
          * 构造一个delete_helper对象
          * @obj: 需要自动删除的对象指针
          * @is_array: 是否为new出来的数组
          */
        DeleteHelper(ObjectType*& obj, bool is_array=false)
            :_obj(obj)
            ,_is_array(is_array)
        {
        }

        /** 析构中，用于自动调用delete或delete []，调用后，指针将被置为NULL */
        ~DeleteHelper()
        {
            if (_is_array)
            {
                delete []_obj;
            }
            else
            {
                delete _obj;
            }

            _obj = NULL; // 由于_obj是obj的引用，所以obj也会受影响
        }

    private:
        ObjectType*& _obj;
        bool _is_array;
    };
};

}

#endif
