#pragma once
#pragma comment(lib, "Ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h> 
#include <iostream>
#include <conio.h>

using namespace std;

#define TIME_PORT	27015
#define USER_MENU_MIN_OPTION 0
#define USER_MENU_MAX_OPTION 13
#define CITY_MENU_MIN_OPTION 1
#define CITY_MENU_MAX_OPTION 5

void printUserMenu();
void printCityMenu();
int getUserRequest();
void closeClient();
bool isInputValid(int userInput);
void sendSimpleRequest(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv);
void getClientToServerDelayEstimation(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv);
void measureRTT(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv);

