//Time_util_test.cpp

#include <iostream>
#include "inc.h"
#include <time.h>
#include "Time_util.h"
using namespace std;
using namespace blp;

void timeUtilTest()
{
	cout << "time util test" << endl;

	cout << "currentDateTime[" << CTimeUtil::currentDateTime() << "]" << endl;
	cout << "currentDate[" << CTimeUtil::currentDate() << "]" << endl;
	cout << "curTime[" << CTimeUtil::curTime() << "]" << endl;
	struct tm tv;
	CTimeUtil::curDateTimeStruct(&tv);
	cout << "toDateTime[" << CTimeUtil::toDateTime(&tv)<< "]" << endl;
	cout << "toDate[" << CTimeUtil::toDate(&tv)<< "]" << endl;
	cout << "toTime[" << CTimeUtil::toTime(&tv)<< "]" << endl;
	cout << "year[" << CTimeUtil::year(&tv)<< "]" << endl;
	cout << "month[" << CTimeUtil::month(&tv)<< "]" << endl;
	cout << "day[" << CTimeUtil::day(&tv)<< "]" << endl;
	cout << "hour[" << CTimeUtil::hour(&tv)<< "]" << endl;
	cout << "minute[" << CTimeUtil::minute(&tv)<< "]" << endl;
	cout << "second[" << CTimeUtil::second(&tv)<< "]" << endl;

	cout << "microSecondsSinceEpoch[" << CTimeUtil::microSecondsSinceEpoch()<< "]" << endl;
	cout << "secondsSinceEpoch[" << CTimeUtil::secondsSinceEpoch()<< "]" << endl;
}