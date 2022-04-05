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
#define MAX_TIME_LAP_DURATION 180

static bool timeLapInProgress = false;
static time_t previousTimeLap;


void getTime(char* sendBuff);
void getTimeWithoutDate(char* sendBuff);
void getTimeSinceEpoch(char* sendBuff);
void getTimeForMeasurement(char* sendBuff);
