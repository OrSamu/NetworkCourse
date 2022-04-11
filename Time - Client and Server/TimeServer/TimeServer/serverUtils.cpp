#include "serverUtils.h"


void getTime(char *sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	sprintf(sendBuff, "Current local time and date: %s", asctime(timeinfo));
}

void getTimeWithoutDate(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "%X", timeinfo);
}

void getTimeSinceEpoch(char* sendBuff)
{
	time_t timeSinceEpoch = time(NULL);

	sprintf(sendBuff, "Time passed since epoch: %lld seconds", timeSinceEpoch);
}

void getTick(char* sendBuff)
{
	DWORD tick = GetTickCount();

	sprintf(sendBuff, "%d", tick);
}

void GetTimeWithoutDateOrSeconds(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "its %H:%M o'clock", timeinfo);
}

void GetYear(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "Current year: %Y", timeinfo);
}

void getMonthAndDay(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "Current month is %B and the day is %d", timeinfo);
}

void getSecondsSinceBeginingOfMonth(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;
	long long difference;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_hour = 0;
	timeinfo->tm_min = 0;
	timeinfo->tm_sec = 0;
	difference = rawtime - mktime(timeinfo);

	sprintf(sendBuff, "Time passed since the beginning of the month: %lld seconds", difference);
}

