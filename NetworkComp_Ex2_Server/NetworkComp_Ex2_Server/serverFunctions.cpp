#include "serverFunctions.h"
int firsMeasureTimeLap = 0;
bool isFirstMeasureTimeRequest = true;
enum clientOpt {
	GetTime = 1,
	GetTimeWithoutDate = 2,
	GetTimeSinceEpoch = 3,
	GetClientToServerDelayEstimation = 4,
	MeasureRTT = 5,
	GetTimeWithoutDateOrSeconds = 6,
	GetYear = 7,
	GetMonthAndDay = 8,
	GetSecondsSinceBeginingOfMonth = 9,
	GetWeekOfYear = 10,
	GetDaylightSavings = 11,
	GetTimeInTokyo = 12,
	GetTimeInMelbourne = 13,
	GetTimeInSanFrancisco = 14,
	GetTimeInPorto = 15,
	GetTimeOfUTC = 16,
	MeasureTimeLap = 17,
	Exit = 18
};
enum TimeDelay {
	Tokyo = 9,
	Melbourne = 10,
	SanFrancisco = -7,
	Porto = 1,
};
void makeClientAnswer(int clientReq, char * sendBuff)
{
	switch (clientReq)
	{
	case GetTime:getTime(sendBuff); break;
	case GetTimeWithoutDate:getTimeWithoutDate(sendBuff); break;
	case GetTimeSinceEpoch:getTimeSinceEpoch(sendBuff); break;
	case GetClientToServerDelayEstimation:getClientToServerDelayEstimation(sendBuff); break;
	case GetTimeWithoutDateOrSeconds:getTimeWithoutDateOrSeconds(sendBuff); break;
	case GetYear:getYear(sendBuff); break;
	case GetMonthAndDay:getMonthAndDay(sendBuff); break;
	case GetSecondsSinceBeginingOfMonth:getSecondsSinceBeginingOfMonth(sendBuff); break;
	case GetWeekOfYear:getWeekOfYear(sendBuff); break;
	case GetDaylightSavings: getDaylightSavings(sendBuff); break;
	case GetTimeInTokyo: getTimeInTokyo(sendBuff); break;
	case GetTimeInMelbourne: getTimeInMelbourne(sendBuff); break;
	case GetTimeInSanFrancisco: getTimeInSanFrancisco(sendBuff); break;
	case GetTimeInPorto: getTimeInPorto(sendBuff); break;
	case GetTimeOfUTC: getTimeOfUTC(sendBuff); break;
	case MeasureTimeLap:measureTimeLap(sendBuff); break;
	default:
		break;
	}

}

void getTime(char * sendBuff)
{
	time_t timer;
	time(&timer);
	strcpy(sendBuff, ctime(&timer));
	sendBuff[strlen(sendBuff) - 1] = '\0';

}

void getTimeInTokyo(char *sendBuff)
{
	time_t now = time(0);
	tm* now_tm = gmtime(&now);
	int hour=(now_tm->tm_hour + Tokyo) % 24;
	sprintf(sendBuff, "Time in Tokyo: %02d:%02d:%02d", hour,now_tm->tm_min, now_tm->tm_sec);
}

void getTimeInMelbourne(char * sendBuff)
{
	time_t now = time(0);
	tm* now_tm = gmtime(&now);
	int hour = (now_tm->tm_hour + Melbourne) % 24;
	sprintf(sendBuff, "Time in Melbourne: %02d:%02d:%02d", hour, now_tm->tm_min, now_tm->tm_sec);
}

void getTimeInSanFrancisco(char * sendBuff)
{
	time_t now = time(0);
	tm* now_tm = gmtime(&now);
	int hour = (now_tm->tm_hour + SanFrancisco) % 24;
	sprintf(sendBuff, "Time in San Francisco: %02d:%02d:%02d", hour, now_tm->tm_min, now_tm->tm_sec);
}

void getTimeInPorto(char * sendBuff)
{
	time_t now = time(0);
	tm* now_tm = gmtime(&now);
	int hour = (now_tm->tm_hour + Porto) % 24;
	sprintf(sendBuff, "Time in Porto: %02d:%02d:%02d", hour, now_tm->tm_min, now_tm->tm_sec);
}

void getTimeOfUTC(char * sendBuff)
{
	time_t now = time(0);
	tm* now_tm = gmtime(&now);
	sprintf(sendBuff, "UTC Time: %02d:%02d:%02d", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
}


void getTimeWithoutDate(char * sendBuff)
{
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	sprintf(sendBuff, "Time with out date: %02d:%02d:%02d", tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
}
void getTimeSinceEpoch(char *sendBuff)
{
	time_t result = time(nullptr);
	sprintf(sendBuff, "Time since epoch: %d", (int)result);
}

void getClientToServerDelayEstimation(char *sendBuff)
{
	int num = GetTickCount();
	sprintf(sendBuff,"%d",num);
}

void getYear(char * sendBuff)
{
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	int year = tm_struct->tm_year + 1900;
	sprintf(sendBuff, "Today Year is : %d ", year);
}

void getMonthAndDay(char * sendBuff)
{
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	int day = tm_struct->tm_mday;
	int month = tm_struct->tm_mon + 1;
	sprintf(sendBuff, "Day:%02d Month: %02d", day, month);
}

void getSecondsSinceBeginingOfMonth(char *sendBuff)
{
	int secondInDay = TimeInHour * TimeInMinute * 24;
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	int dayOfMonth = tm_struct->tm_mday;
	int min = tm_struct->tm_min;
	int hour = tm_struct->tm_hour;
	int sec = tm_struct->tm_sec;
	int sumOfSecond = (dayOfMonth * secondInDay) + (hour*TimeInHour *TimeInMinute) + (min*TimeInMinute) + sec;
	sprintf(sendBuff, "Seconds Since Begining Of Month : %d ", sumOfSecond);
}
void getWeekOfYear(char *sendBuff)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sendBuff, 255, "Number of the week: %U", timeinfo);

}

void getDaylightSavings(char *sendBuff)
{
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	itoa(tm_struct->tm_isdst, sendBuff, 10);
}

void getTimeWithoutDateOrSeconds(char *sendBuff)
{
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	int hour = tm_struct->tm_hour;
	int min = tm_struct->tm_min;
	sprintf(sendBuff, "Time: %02d:%02d", hour, min);
}

void measureTimeLap(char* sendBuff) {

	int secondMeasureTimeLap=0, measureTimeDifference=0;
	char startMeasureTimeMsg[100];
	strcpy(startMeasureTimeMsg, "Starting to ticking..");
	if (isFirstMeasureTimeRequest)
	{
		firsMeasureTimeLap = GetTickCount();
		sprintf(sendBuff, "%s ", startMeasureTimeMsg);
		isFirstMeasureTimeRequest = FALSE;
	}
	else
	{
		secondMeasureTimeLap = GetTickCount();
		measureTimeDifference = (secondMeasureTimeLap - firsMeasureTimeLap);
		if (measureTimeDifference <= ThreeMinInMiliseconds)
		{
			sprintf(sendBuff, "The measure time lap difference is:%d milliseconds. ", measureTimeDifference);
		}
		else
		{
			firsMeasureTimeLap = secondMeasureTimeLap;
			sprintf(sendBuff, "%s ", startMeasureTimeMsg);
		}
		isFirstMeasureTimeRequest = TRUE;
	}
}

void openServer()
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}
	SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	sockaddr_in serverService;
	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = INADDR_ANY;
	serverService.sin_port = htons(TIME_PORT);
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR *)&serverService, sizeof(serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}
	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	int bytesSent = 0, bytesRecv = 0;
	char sendBuff[255], recvBuff[255];
	cout << "Time Server: Wait for clients' requests.\n";
	while (true)
	{
		bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, &client_addr, &client_addr_len);
		recvBuff[bytesRecv] = '\0';
		int clientChoice = atoi(recvBuff);
		makeClientAnswer(clientChoice, sendBuff);
		if (SOCKET_ERROR == bytesRecv)
		{
			cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		cout << recvBuff << "\n";
		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		cout << "Time Server: Sent: " << sendBuff << " message.\n";
	}
	cout << "Time Server: Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}
