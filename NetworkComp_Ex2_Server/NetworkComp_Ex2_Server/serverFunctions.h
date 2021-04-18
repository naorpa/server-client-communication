#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include<windows.h>
#include <ctime>
#pragma warning(disable: 4996)
#define TIME_PORT	27015
#define TimeInHour 60
#define TimeInMinute 60
# define ThreeMinInMiliseconds 60*3*1000



void getTimeSinceEpoch(char *sendBuff);
void makeClientAnswer(int clientReq,char *sendBuff);
void getTime(char *sendBuff);
void getTimeWithoutDate(char * sendBuff);
void getClientToServerDelayEstimation(char *sendBuff);
void getYear(char * sendBuff);
void getMonthAndDay(char * sendBuff);
void getSecondsSinceBeginingOfMonth(char *sendBuff);
void getWeekOfYear(char *sendBuff);
void getDaylightSavings(char *sendBuff);
void getTimeWithoutDateOrSeconds(char *sendBuff);
void getTimeInTokyo(char *sendBuff);
void getTimeInMelbourne(char *sendBuff);
void getTimeInSanFrancisco(char *sendBuff);
void getTimeInPorto(char *sendBuff);
void getTimeOfUTC(char *sendBuff);
void measureTimeLap(char* sendBuff);
void openServer();

