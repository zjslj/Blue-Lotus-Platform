//String_util.cpp
#include "String_util.h"
#include "Utils.h"
#include <stdarg.h>
#include <limits>

using namespace blp;
void CStringUtil::remove_last(std::string& src, char c)
{
	std::string::size_type pos = src.rfind(c);
    if(pos+1 != src.length())
    {
        src.erase(pos);
    }
}

void CStringUtil::remove_last(std::string& src, const std::string& sep)
{
	std::string::size_type pos = src.rfind(sep);
    if(pos != std::string::npos)
    {
        src.erase(pos);
    }
}

void CStringUtil::to_upper(char* src)
{
	char* tmpSrc = src;
    while(*tmpSrc != '\0')
    {
        if((*tmpSrc >= 'a') &&(*tmpSrc <= 'z'))
        {
            *tmpSrc += 'A' - 'a';
		}
        ++tmpSrc;
    }
}

void CStringUtil::to_upper(std::string& src)
{
	char* tmpSrc =(char *)src.c_str();
    to_upper(tmpSrc);
}

void CStringUtil::to_lower(char* src)
{
	char* tmpSrc = src;
    while(*tmpSrc != '\0')
    {
        if((*tmpSrc >= 'A') &&(*tmpSrc <= 'Z'))
        {
            *tmpSrc += 'a' - 'A';
		}
        ++tmpSrc;
    }
}

void CStringUtil::to_lower(std::string& src)
{
	char* tmpSrc =(char *)src.c_str();
    to_lower(tmpSrc);
}

bool CStringUtil::is_space(char c)
{
	return(' ' == c) ||('\t' == c) ||('\r' == c) ||('\n' == c);
}

void CStringUtil::trim(char* src)
{
	char* space = NULL;
    char* tmpSrc = src;
    while(' ' == *tmpSrc) 
    {
    	++tmpSrc;
	}

    for(;;)
    {
        *src = *tmpSrc;
        if('\0' == *tmpSrc)
        {
            if(space != NULL)
            {
                *space = '\0';
            }
            break;
        }
        else if(is_space(*tmpSrc))
        {
            if(NULL == space)
            {
                space = src;
            }
        }
        else
        {
            space = NULL;
        }

        ++src;
        ++tmpSrc;
    }
}

void CStringUtil::trim(std::string& src)
{
	trim_left(src);
    trim_right(src);
}

void CStringUtil::trim_left(char* src)
{
    char* tmpSrc = src;
    while(is_space(*tmpSrc))
    {
    	++tmpSrc;
    }

    for(;;)
    {
        *src = *tmpSrc;
        if('\0' == *tmpSrc) 
        {
        	break;
		}

        ++src;
        ++tmpSrc;
    }
}

void CStringUtil::trim_left(std::string& src)
{
	// 不能直接对c_str()进行修改，因为长度发生了变化
    size_t length = src.length();
    char* tmpSrc = new char[length+1];
    CUtils::DeleteHelper<char> dh(tmpSrc, true);

    strncpy(tmpSrc, src.c_str(), length);
    tmpSrc[length] = '\0';

    trim_left(tmpSrc);
    src = tmpSrc;
}

void CStringUtil::trim_right(char* src)
{
    char* space = NULL;
    char* tmpSrc = src;

    for(;;)
    {
        if('\0' == *tmpSrc)
        {
            if(space != NULL)
            {
                *space = '\0';
            }
            break;
        }
        else if(is_space(*tmpSrc))
        {
            if(NULL == space)
            {
                space = tmpSrc;
            }
        }
        else
        {
            space = NULL;
        }

        ++tmpSrc;
    }
}       

void CStringUtil::trim_right(std::string& src)
{
    // 不能直接对c_str()进行修改，因为长度发生了变化
    size_t length = src.length();
    char* tmpSrc = new char[length+1];
    CUtils::DeleteHelper<char> dh(tmpSrc, true);

    strncpy(tmpSrc, src.c_str(), length);
    tmpSrc[length] = '\0';

    trim_right(tmpSrc);
    src = tmpSrc;
}

int CStringUtil::chr_index(const char* str, char c)
{
    const char* pos = strchr(str, c);
    return (NULL == pos)? -1: pos-str;
}

int CStringUtil::chr_rindex(const char* str, char c)
{
	const char* pos = strrchr(str, c);
    return (NULL == pos)? -1: pos-str;
}

std::string CStringUtil::format_string(const char* format, ...) 
{
	va_list ap;
    va_start(ap, format);

    // size不包含结尾符，所以在分配内存时需要加一
    size_t size = 1024;
    char* buffer = new char[size + 1];

    // vsnprintf中的第二参数大小是要求包含结尾符的
    int expected = vsnprintf(buffer, size + 1, format, ap);
    if (expected >= ((int)size+1))
    {
        // 防止太长，撑死内存
        if (expected > 10240)
            expected = 10240;

        // expected的大小不包含结尾符，所以在分配内存时需要加一
        delete []buffer;
        buffer = new char[expected + 1];

        va_end(ap);
        va_start(ap, format);

        vsnprintf(buffer, static_cast<size_t>(expected + 1), format, ap);
    }

    va_end(ap);
    CUtils::DeleteHelper<char> dh(buffer, true);
    return buffer;
}

