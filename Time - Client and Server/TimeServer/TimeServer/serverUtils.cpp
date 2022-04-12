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

void getTimeWithoutDateOrSeconds(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "its %H:%M o'clock", timeinfo);
}

void getYear(char* sendBuff)
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

void getWeekOfYear(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "This is the %U week of the year", timeinfo);
}

void getDaylightSavings(char* sendBuff)
{
	time_t rawtime;
	struct tm* timeinfo;
	char* daylightSavings;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	sprintf(sendBuff, "Current Daylight Savings: %s Time", timeinfo->tm_isdst ? "Summer" : "Winter");
}

void getTimeWithoutDateInCity(char* recvBuff, char* sendBuff, SOCKET m_socket, sockaddr client_addr, int client_addr_len)
{
	time_t rawtime;
	struct tm* timeinfo;
	int cityDiff = 0;
	int bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, &client_addr, &client_addr_len);

	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "UDP Server: Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "UDP Server: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";

	int city = atoi(recvBuff);

	switch (city)
	{
	case 1:
		//Tokyo (Japan)
		cityDiff = 9;
		break;
	case 2:
		//Melbourne (Australia)
		cityDiff = 10;
		break;
	case 3:
		//San Francisco (USA)
		cityDiff = -7;
		break;
	case 4:
		//Porto (Portugal)
		cityDiff = 1;
		break;
	default:
		//Other (UTC)
		cityDiff = 0;
		break;
	}

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	timeinfo->tm_hour = (timeinfo->tm_hour + cityDiff) % 24;
	strftime(sendBuff, 255, "%X", timeinfo);
}

void measureTimeLap(char* sendBuff, bool *inTimeLap, DWORD *timeLapStart)
{
	if (*inTimeLap)
	{
		DWORD timeLapCurrent = GetTickCount();

		sprintf(sendBuff, "Time lap measurement ended, duration: %lld ms", timeLapCurrent - *timeLapStart);
		*inTimeLap = false;

		return;
	}

	*inTimeLap = true;
	*timeLapStart = GetTickCount();
	sprintf(sendBuff, "Starting time lap measurement");
	
	return;
}