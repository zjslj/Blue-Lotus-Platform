#include "Time_util.h"
#include "String_util.h"
#include <stddef.h>
#include <sys/time.h>

using namespace blp;


void CTimeUtil::curDateTime(char* buf, size_t bufSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buf, bufSize
        ,"%04d-%02d-%02d %02d:%02d:%02d"
        ,result.tm_year+1900, result.tm_mon+1, result.tm_mday
        ,result.tm_hour, result.tm_min, result.tm_sec);
}

std::string CTimeUtil::currentDateTime()
{
	char buf[sizeof("YYYY-MM-DD HH:MM:SS")];
    curDateTime(buf, sizeof(buf));
    return buf;
}

void CTimeUtil::currentDate(char* buf, size_t bufSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buf, bufSize
        ,"%04d-%02d-%02d"
        ,result.tm_year+1900, result.tm_mon+1, result.tm_mday);
}
std::string CTimeUtil::currentDate()
{
	char buf[sizeof("YYYY-MM-DD")];
    currentDate(buf, sizeof(buf));
    return buf;
} 

void CTimeUtil::curTime(char* buf, size_t bufSize)
{
	struct tm result;
    time_t now = time(NULL);

    localtime_r(&now, &result);
    snprintf(buf, bufSize
        ,"%02d:%02d:%02d"
        ,result.tm_hour, result.tm_min, result.tm_sec);
}
std::string CTimeUtil::curTime()
{
	char buf[sizeof("HH:MM:SS")];
    curTime(buf, sizeof(buf));
    return buf;
}


void CTimeUtil::curDateTimeStruct(struct tm* stDateTime)
{
	time_t now = time(NULL);
    localtime_r(&now, stDateTime);
}

void CTimeUtil::toDateTime(struct tm* stDateTime, char* buf, size_t bufSize)
{
    snprintf(buf, bufSize
        ,"%04d-%02d-%02d %02d:%02d:%02d"
        ,stDateTime->tm_year+1900, stDateTime->tm_mon+1, stDateTime->tm_mday
        ,stDateTime->tm_hour, stDateTime->tm_min, stDateTime->tm_sec);
}
std::string CTimeUtil::toDateTime(struct tm* stDateTime)
{
	char buf[sizeof("YYYY-MM-DD HH:MM:SS")];
    toDateTime(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::toDate(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize
        ,"%04d-%02d-%02d"
        ,stDateTime->tm_year+1900, stDateTime->tm_mon+1, stDateTime->tm_mday);
}
std::string CTimeUtil::toDate(struct tm* stDateTime)
{
	char buf[sizeof("YYYY-MM-DD")];
    toDate(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::toTime(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize
        ,"%02d:%02d:%02d"
        ,stDateTime->tm_hour, stDateTime->tm_min, stDateTime->tm_sec);
}
std::string CTimeUtil::toTime(struct tm* stDateTime)
{
	char buf[sizeof("HH:MM:SS")];
    toTime(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::year(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%04d", stDateTime->tm_year+1900);
}
std::string CTimeUtil::year(struct tm* stDateTime)
{
	char buf[sizeof("YYYY")];
    year(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::month(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%02d", stDateTime->tm_mon+1);
}
std::string CTimeUtil::month(struct tm* stDateTime)
{
	char buf[sizeof("MM")];
    month(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::day(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%02d", stDateTime->tm_mday);
}
std::string CTimeUtil::day(struct tm* stDateTime)
{
	char buf[sizeof("DD")];
    day(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::hour(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%02d", stDateTime->tm_hour);
}
std::string CTimeUtil::hour(struct tm* stDateTime)
{
	char buf[sizeof("HH")];
    hour(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::minute(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%02d", stDateTime->tm_min);
}
std::string CTimeUtil::minute(struct tm* stDateTime)
{
	char buf[sizeof("MM")];
    minute(stDateTime, buf, sizeof(buf));
    return buf;
}

void CTimeUtil::second(struct tm* stDateTime, char* buf, size_t bufSize)
{
	snprintf(buf, bufSize, "%02d", stDateTime->tm_sec);
}
std::string CTimeUtil::second(struct tm* stDateTime)
{
	char buf[sizeof("SS")];
    second(stDateTime, buf, sizeof(buf));
    return buf;
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