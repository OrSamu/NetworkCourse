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

	sprintf(sendBuff, "Time since epoch: %lld seconds", timeSinceEpoch);
}

void getTick(char* sendBuff)
{
	DWORD tick = GetTickCount();

	sprintf(sendBuff, "%d", tick);
}