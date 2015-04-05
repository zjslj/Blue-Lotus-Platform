#ifndef _BLP_BASE_TIME_UTIL_H
#define _BLP_BASE_TIME_UTIL_H

#include <time.h>
#include <stdint.h>
#include <string>

namespace blp{
class CTimeUtil{
public:
	struct YearMonthDay
	{
		int year; // [1900..2500]
		int month;  // [1..12]
		int day;  // [1..31]
	};
	static const int kDaysPerWeek = 7;
	static const int kSecondsPerDay = 86400;
	static const int kMicroSecondsPerSecond = 1000 * 1000;
	/** 获取当前时间，返回格式为: YYYY-MM-DD HH:SS:MM
      * @buff: 用来存储当前日期和时间的缓冲区
      * @buffSize: buff的字节大小，不应当于小“YYYY-MM-DD HH:SS:MM”
      */
    static void curDateTime(char* buff, size_t buffSize);
    static std::string currentDateTime();

    /** 获取当前日期，返回格式为: YYYY-MM-DD
      * @buff: 用来存储当前日期的缓冲区
      * @buffSize: buff的字节大小，不应当于小“YYYY-MM-DD”
      */
    static void currentDate(char* buff, size_t buffSize);
    static std::string currentDate(); 

    /** 得到当前时间，返回格式为: HH:SS:MM
      * @buff: 用来存储当前时间的缓冲区
      * @buffSize: buff的字节大小，不应当于小“HH:SS:MM”
      */
    static void curTime(char* buff, size_t buffSize);
    static std::string curTime(); 

    /** 得到当前日期和时间结构
      * @stDateTime: 指向当前日期和时间结构的指针
      */
    static void curDateTimeStruct(struct tm* stDateTime);

    /** 日期和时间 */
    static void toDateTime(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string toDateTime(struct tm* stDateTime);

    /** 仅日期 */
    static void toDate(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string toDate(struct tm* stDateTime);

    /** 仅时间 */
    static void toTime(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string toTime(struct tm* stDateTime);

    /** 仅年份 */
    static void year(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string year(struct tm* stDateTime);

    /** 仅月份 */
    static void month(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string month(struct tm* stDateTime);

    /** 仅天 */
    static void day(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string day(struct tm* stDateTime);

    /** 仅小时 */
    static void hour(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string hour(struct tm* stDateTime);

    /** 仅分钟 */
    static void minute(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string minute(struct tm* stDateTime);

    /** 仅秒钟 */
    static void second(struct tm* stDateTime, char* buff, size_t buffSize);
    static std::string second(struct tm* stDateTime);

    /**timestamp*/
    static int64_t microSecondsSinceEpoch();
    static time_t secondsSinceEpoch();



};
}


#endif