#pragma once
#pragma comment(lib, "Ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <string>
#include <time.h>

#define TIME_PORT	27015
#define MAX_TIME_LAP_DURATION 180000

static bool timeLapInProgress = false;
static time_t previousTimeLap;

void getTime(char* sendBuff);
void getTimeWithoutDate(char* sendBuff);
void getTimeSinceEpoch(char* sendBuff);
void getTick(char* sendBuff);
void getTimeWithoutDateOrSeconds(char* sendBuff);
void getYear(char* sendBuff);
void getMonthAndDay(char* sendBuff);
void getSecondsSinceBeginingOfMonth(char* sendBuff);
void getWeekOfYear(char* sendBuff);
void getDaylightSavings(char* sendBuff);
void getTimeWithoutDateInCity(char* recvBuff, char* sendBuff, SOCKET m_socket, sockaddr client_addr, int client_addr_len);
void measureTimeLap(char* sendBuff, bool* inTimeLap, DWORD* startedAt);
