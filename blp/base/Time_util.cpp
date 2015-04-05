#include "Time_util.h"
#include "String_util.h"
#include <stddef.h>
#include <sys/time.h>

using namespace blp;


void CTimeUtil::curDateTime(char* buff, size_t buffSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buff, buffSize
        ,"%04d-%02d-%02d %02d:%02d:%02d"
        ,result.tm_year+1900, result.tm_mon+1, result.tm_mday
        ,result.tm_hour, result.tm_min, result.tm_sec);
}

std::string CTimeUtil::currentDateTime()
{
	char buff[sizeof("YYYY-MM-DD HH:MM:SS")];
    curDateTime(buff, sizeof(buff));
    return buff;
}

void CTimeUtil::currentDate(char* buff, size_t buffSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buff, buffSize
        ,"%04d-%02d-%02d"
        ,result.tm_year+1900, result.tm_mon+1, result.tm_mday);
}
std::string CTimeUtil::currentDate()
{
	char buff[sizeof("YYYY-MM-DD")];
    currentDate(buff, sizeof(buff));
    return buff;
} 

void CTimeUtil::curTime(char* buff, size_t buffSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buff, buffSize
        ,"%02d:%02d:%02d"
        ,result.tm_hour, result.tm_min, result.tm_sec);
}
std::string CTimeUtil::curTime()
{
	char buff[sizeof("HH:MM:SS")];
    curTime(buff, sizeof(buff));
    return buff;
}


void CTimeUtil::curDateTimeStruct(struct tm* stDateTime)
{
	time_t now = time(NULL);
    localtime_r(&now, stDateTime);
}

void CTimeUtil::toDateTime(struct tm* stDateTime, char* buff, size_t buffSize)
{
    snprintf(buff, buffSize
        ,"%04d-%02d-%02d %02d:%02d:%02d"
        ,stDateTime->tm_year+1900, stDateTime->tm_mon+1, stDateTime->tm_mday
        ,stDateTime->tm_hour, stDateTime->tm_min, stDateTime->tm_sec);
}
std::string CTimeUtil::toDateTime(struct tm* stDateTime)
{
	char buff[sizeof("YYYY-MM-DD HH:MM:SS")];
    toDateTime(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::toDate(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize
        ,"%04d-%02d-%02d"
        ,stDateTime->tm_year+1900, stDateTime->tm_mon+1, stDateTime->tm_mday);
}
std::string CTimeUtil::toDate(struct tm* stDateTime)
{
	char buff[sizeof("YYYY-MM-DD")];
    toDate(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::toTime(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize
        ,"%02d:%02d:%02d"
        ,stDateTime->tm_hour, stDateTime->tm_min, stDateTime->tm_sec);
}
std::string CTimeUtil::toTime(struct tm* stDateTime)
{
	char buff[sizeof("HH:MM:SS")];
    toTime(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::year(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%04d", stDateTime->tm_year+1900);
}
std::string CTimeUtil::year(struct tm* stDateTime)
{
	char buff[sizeof("YYYY")];
    year(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::month(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%02d", stDateTime->tm_mon+1);
}
std::string CTimeUtil::month(struct tm* stDateTime)
{
	char buff[sizeof("MM")];
    month(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::day(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%02d", stDateTime->tm_mday);
}
std::string CTimeUtil::day(struct tm* stDateTime)
{
	char buff[sizeof("DD")];
    day(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::hour(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%02d", stDateTime->tm_hour);
}
std::string CTimeUtil::hour(struct tm* stDateTime)
{
	char buff[sizeof("HH")];
    hour(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::minute(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%02d", stDateTime->tm_min);
}
std::string CTimeUtil::minute(struct tm* stDateTime)
{
	char buff[sizeof("MM")];
    minute(stDateTime, buff, sizeof(buff));
    return buff;
}

void CTimeUtil::second(struct tm* stDateTime, char* buff, size_t buffSize)
{
	snprintf(buff, buffSize, "%02d", stDateTime->tm_sec);
}
std::string CTimeUtil::second(struct tm* stDateTime)
{
	char buff[sizeof("SS")];
    second(stDateTime, buff, sizeof(buff));
    return buff;
}

int64_t CTimeUtil::microSecondsSinceEpoch()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;

    return seconds * kMicroSecondsPerSecond + tv.tv_usec;
}
time_t CTimeUtil::secondsSinceEpoch()
{
	return static_cast<time_t>(microSecondsSinceEpoch() / kMicroSecondsPerSecond);
}