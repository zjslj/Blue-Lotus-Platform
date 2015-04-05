#ifndef BLP_BASE_CONFIG_H
#define BLP_BASE_CONFIG_H
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits> // std::numeric_limits<>
#include <stdarg.h> // va_list
#include <stddef.h> // offsetof
#include <string> // std::string
#include <string.h>
#include <stdint.h> // int32_t
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS // PRId64
#endif

#include <inttypes.h>

namespace blp{

/***
 * 常量定义
 */
enum
{
    MAX_DATETIME_SIZE = (sizeof("YYYY-MM-DD hh:mm:ss") - 1), // 日期时间的标准（YYYY-MM-DD hh:mm:ss）格式字符个数
    DATA_FILE_MODE_DEFAULT = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, // 文件权限模式：数据文件、文本文件、配置文件等默认权限
};

}
#endif	
	
