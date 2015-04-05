// 使用方法：
// 1) 构造一个CLogger对象
//    CLogger logger(".", "test.log", 1024*1024, 10);
// 2) 调用print方法写日志
//    logger.info(__FILE__, __LINE__, "%s\n", "test");

#ifndef BLP_BASE_LOGGER_H
#define BLP_BASE_LOGGER_H
#include <time.h>
#include <string>
#include <sys/uio.h>
#include "File_locker.h"
#include "Scoped_ptr.h"
#include "Utils.h"
#include "String_util.h"

/**
 * 便于使用的日志宏
 */

// Raw
#define RAW(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else { \
        logger->raw(format, ##__VA_ARGS__); \
    } \
} while(false)

// Debug
#define DEBUG(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf("[DEBUG][%s:%d]", __FILE__, __LINE__); \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else if (logger->enabled_debug()) { \
        logger->debug(__FILE__, __LINE__, format, ##__VA_ARGS__); \
    } \
} while(false)

// Info
#define INFO(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf("[INFO][%s:%d]", __FILE__, __LINE__); \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else if (logger->enabled_info()) { \
        logger->info(__FILE__, __LINE__, format, ##__VA_ARGS__); \
    } \
} while(false)

// Error
#define ERROR(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf("[ERROR][%s:%d]", __FILE__, __LINE__); \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else if (logger->enabled_error()) { \
        logger->error(__FILE__, __LINE__, format, ##__VA_ARGS__); \
    } \
} while(false)

// Warning
#define WARNING(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf("[WARNING][%s:%d]", __FILE__, __LINE__); \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else if (logger->enabled_warning()) { \
        logger->warning(__FILE__, __LINE__, format, ##__VA_ARGS__); \
    } \
} while(false)

// Fatal
#define FATAL(logger, format, ...) \
do { \
    if (NULL == logger) { \
        printf("[FATAL][%s:%d]", __FILE__, __LINE__); \
        printf(format, ##__VA_ARGS__); \
        printf("\n"); \
    } \
    else if (logger->enabled_fetal()) { \
        logger->fatal(__FILE__, __LINE__, format, ##__VA_ARGS__); \
    } \
} while(false)

namespace blp{

/***
 * 支持按文件大小滚动日志记录器，支持多进程写同一个日志文件
 */
class CLogger
{
public:
    /***
      * 构造一个CLogger，并创建或打开日志文件
      * @log_dir 日志存放的目录，不需要以斜杠结尾，目录必须已经存在
      * @filename 日志的文件名，不包含目录部分，
      *           由log_dir和filename共同组成日志文件路径
      * @log_size 每个日志文件的大小，单位为字节数，如果小于1024，则会被强制为1024
      * @log_numer 日志滚动的个数
      * @record_size 单条日志的大小，超过会被截断，单位为字节数，如果小于1024，则会被强制为1024
      */
    explicit CLogger(const std::string& log_dir,
                           const std::string& filename,
                           uint32_t log_size = 1024*1024*100,
                           uint8_t log_numer = 10,
                           time_t roll_interval = 86400,
                           uint16_t record_size = 8192);
    ~CLogger();

    /** 日志文件是否创建或打开成功 */
    bool is_ok() const;

    /** 输出日志，象printf一样使用，不自动加换行符 */
    void raw(const char* format, ...) __attribute__((format(printf, 2, 3)));
    void debug(const char* file, int line, const char* format, ...) __attribute__((format(printf, 4, 5)));
    void info(const char* file, int line, const char* format, ...) __attribute__((format(printf, 4, 5)));
    void error(const char* file, int line, const char* format, ...) __attribute__((format(printf, 4, 5)));
    void warning(const char* file, int line, const char* format, ...) __attribute__((format(printf, 4, 5)));
    void fatal(const char* file, int line, const char* format, ...) __attribute__((format(printf, 4, 5)));

    /** 得到含文件名的日志文件路径*/
    const std::string& get_log_filepath() const;

    /** 设置tag */
    template <typename IntType>
    void set_tag1(IntType tag);
    void set_tag1(const std::string& tag);
    template <typename IntType>
    void set_tag2(IntType tag);
    void set_tag2(const std::string& tag);

    /** 判断某种级别的日志是否可输出 */
    bool enabled_debug() const;
    bool enabled_info() const;
    bool enabled_error() const;
    bool enabled_warning() const;
    bool enabled_fetal() const;

private:
    void print(const char* file, int line, const char* level, const char* format, va_list& ap);
    bool need_rotate(); /** 是否需要滚动了 */
    void reset();             /** 复位状态值 */
    void rotate_log();        /** 滚动日志 */
	void set_file_name(std::string file_name);
	void openfile();

private:
    int _fd;                   /** 当前正在写的日志文件描述符 */
    std::string _log_dir;      /** 日志存放目录 */
    std::string _filename;     /** 日志文件名，不包含目录部分 */
	std::string _file_stamp;   /**日志文件时间标签，用于构造日志文件名*/
    uint32_t _log_size;        /** 单个日志文件的大小 */
    uint8_t _log_numer;        /** 日志滚动的个数 */
	time_t _roll_interval;
    uint16_t _record_size;     /** 单条日志的大小，单位为字节数 */
    std::string _log_filepath; /** 含文件名的日志文件路径 */
    std::string _tag1;          /** 自定义的标记1 */
    std::string _tag2;          /** 自定义的标记2 */
	time_t _last_roll_time;
	uint8_t _roll_type;			/**日志文件切换的原因，0大小，1时间*/
};
}
#endif 

