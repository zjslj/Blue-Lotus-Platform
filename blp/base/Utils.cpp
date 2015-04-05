#include "Utils.h"
#include "Config.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits>
#include "Scoped_ptr.h"

using namespace blp;

int64_t CUtils::get_filesize(int fd)
{
    return static_cast<int64_t>(lseek(fd, 0, SEEK_END));
}

time_t CUtils::get_file_modify_time(int fd)
{
    struct stat stStat;
    if(fstat(fd, &stStat))
    {
        return -1;
    }
    else
    {
        return stStat.st_mtime;
    }    
}

std::string CUtils::int_tostring(int16_t source)
{
    char str[sizeof("065535")]; // 0xFFFF
    snprintf(str, sizeof(str), "%d", source);
    return str;
}

std::string CUtils::int_tostring(int32_t source)
{
    char str[sizeof("04294967295")]; // 0xFFFFFFFF
    snprintf(str, sizeof(str), "%d", source);
    return str;
}


std::string CUtils::int_tostring(int64_t source)
{
    char str[sizeof("018446744073709551615")]; // 0xFFFFFFFFFFFFFFFF
    snprintf(str, sizeof(str), "%"PRId64, source);
    return str;
}

std::string CUtils::int_tostring(uint16_t source)
{
    char str[sizeof("065535")]; // 0xFFFF
    snprintf(str, sizeof(str), "%u", source);
    return str;
}


std::string CUtils::int_tostring(uint32_t source)
{
    char str[sizeof("04294967295")]; // 0xFFFFFFFF
    snprintf(str, sizeof(str), "%u", source);
    return str;
}

std::string CUtils::int_tostring(uint64_t source)
{
    char str[sizeof("018446744073709551615")]; // 0xFFFFFFFFFFFFFFFF
#if __WORDSIZE==64
    snprintf(str, sizeof(str), "%lu", source);
#else
    snprintf(str, sizeof(str), "%llu", source);
#endif
    return str;
}

int CUtils::fix_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    int expected = vsnprintf(str, size, format, ap);

    if (expected < static_cast<int>(size))
        return expected + 1;

    return static_cast<int>(size);
}


