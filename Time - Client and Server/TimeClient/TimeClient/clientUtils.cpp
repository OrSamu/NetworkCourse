#include "clientUtils.h"

void printUserMenu()
{
    system("cls");

    cout << "~~~~~~~~~~~~~~~ Main Menu ~~~~~~~~~~~~~~~" << endl;
    cout << "Enter the number for the desired command" << endl;
    cout << "1.  Get Time - will return current date and time" << endl;
    cout << "2.  Get Time Without Date - will return only the current time  " << endl;
    cout << "3.  Get Time Since Epoch - will return seconds passed from 01.01.1970 until now" << endl;
    cout << "4.  Get Client To Server Delay Estimation" << endl;
    cout << "5.  Measure RTT - will measure the round trip time" << endl;
    cout << "6.  Get Time Without Date Or Seconds - will return time by hh:mm" << endl;
    cout << "7.  Get Year - will return the current year" << endl;
    cout << "8.  Get Month and Day - will return the current day and month" << endl;
    cout << "9.  Get Seconds Since Begining Of Month - will return the number of seconds passed from the start of the month" << endl;
    cout << "10. Get Week Of Year - will return the number of week since the start of the year" << endl;
    cout << "11. Get Daylight Savings - will return if the daylight saving is on or off" << endl;
    cout << "12. Get Time Without Date In City - will return the time in chosen city" << endl;
    cout << "13. Measure Time Lap - will return the time past between client's requests (up to 3 minutes)" << endl;
    cout << "To exit enter any other char" << endl;
}

void printCityMenu()
{
    cout << "***** City Menu *****" << endl;
    cout << "Enter the number for the desired city" << endl;
    cout << "1.  Tokyo (Japan)" << endl;
    cout << "2.  Melbourne (Australia)" << endl;
    cout << "3.  San Francisco (USA)" << endl;
    cout << "4.  Porto (Portugal)" << endl;
    cout << "5.  Other (UTC General Time)" << endl;
}

int getUserRequest(int minReq, int maxReq)
{
    int userInput;
    bool keepCheckingForValidation = true;

    while (keepCheckingForValidation)
    {
        cin >> userInput;
        isInputValid(userInput, minReq, maxReq) ? keepCheckingForValidation = false : keepCheckingForValidation = true;
        if (keepCheckingForValidation)
        {
            cout << "Invalid selection, please try again" << endl;
        }
    }

	return userInput;
}

void closeClient()
{
	char bye;
    bool waitForKeyPress = true;

	system("cls");
	cout << "Bye bye - press any key to exit the program" << endl;

    return;
}

bool isInputValid(int userInput, int minReq, int maxReq)
{
    return userInput >= minReq && userInput <= maxReq;
}

void sendSimpleRequest(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv)
{
    // The send function sends data on a connected socket.
    // The buffer to be sent and its size are needed.
    // The fourth argument is an idicator specifying the way in which the call is made (0 for default).
    // The two last arguments hold the details of the server to communicate with. 
     // NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
    bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
    if (SOCKET_ERROR == bytesSent)
    {
        cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return;
    }
    cout << "UDP Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

    // Gets the server's answer using simple recieve (no need to hold the server's address).
    bytesRecv = recv(connSocket, recvBuff, 255, 0);
    if (SOCKET_ERROR == bytesRecv)
    {
        cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return;
    }

    recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
    cout << "UDP Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";

    std::system("pause");
}

void getClientToServerDelayEstimation(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv)
{
    float clientToServerdelay = 0, avgDelay;
    unsigned long lastResponse, currentResponse;

    for (int i = 0; i < 100; i++)
    {
        // The send function sends data on a connected socket.
        // The buffer to be sent and its size are needed.
        // The fourth argument is an idicator specifying the way in which the call is made (0 for default).
        // The two last arguments hold the details of the server to communicate with. 
        // NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
        bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
        if (SOCKET_ERROR == bytesSent)
        {
            cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
            closesocket(connSocket);
            WSACleanup();
            return;
        }
    }

    for (int i = 0; i < 100; i++)
    {
        // Gets the server's answer using simple recieve (no need to hold the server's address).
        bytesRecv = recv(connSocket, recvBuff, 255, 0);
        if (SOCKET_ERROR == bytesRecv)
        {
            cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
            closesocket(connSocket);
            WSACleanup();
            return;
        }

        recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
        currentResponse = strtoul(recvBuff, nullptr, 0);

        if (i > 0)
        {
            clientToServerdelay = clientToServerdelay + (float)(currentResponse - lastResponse);
        }

        lastResponse = currentResponse;
    }

    avgDelay = clientToServerdelay / 100;
    cout << "The average client to server delay is: " << avgDelay << "ms" << endl;
    std::system("pause");
}

void measureRTT(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv)
{
    float clientToServerdelay = 0, avgDelay;
    unsigned long valueWhenSent, valueWhenReceived;

    for (int i = 0; i < 100; i++)
    {
        // The send function sends data on a connected socket.
        // The buffer to be sent and its size are needed.
        // The fourth argument is an idicator specifying the way in which the call is made (0 for default).
        // The two last arguments hold the details of the server to communicate with. 
        // NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
        bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
        valueWhenSent = GetTickCount();
        if (SOCKET_ERROR == bytesSent)
        {
            cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
            closesocket(connSocket);
            WSACleanup();
            return;
        }

        // Gets the server's answer using simple recieve (no need to hold the server's address).
        bytesRecv = recv(connSocket, recvBuff, 255, 0);
        valueWhenReceived = GetTickCount();
        if (SOCKET_ERROR == bytesRecv)
        {
            cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
            closesocket(connSocket);
            WSACleanup();
            return;
        }

        clientToServerdelay = clientToServerdelay + (float)(valueWhenReceived - valueWhenSent);
    }

    avgDelay = clientToServerdelay / 100;
    cout << "The average RTT delay is: " << avgDelay << "ms" << endl;
    std::system("pause");
}

void getTimeWithoutDateInCity(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server, int& bytesSent, int& bytesRecv)
{
    bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
    if (SOCKET_ERROR == bytesSent)
    {
        cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return;
    }
    cout << "UDP Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

    printCityMenu();

    int usersRequest = getUserRequest(CITY_MENU_MIN_OPTION, CITY_MENU_MAX_OPTION);
    char newSendBuff[255];

    sprintf_s(newSendBuff, "%d", usersRequest);
    bytesSent = sendto(connSocket, newSendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
    if (SOCKET_ERROR == bytesSent)
    {
        cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return;
    }
    cout << "UDP Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

    bytesRecv = recv(connSocket, recvBuff, 255, 0);
    if (SOCKET_ERROR == bytesRecv)
    {
        cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return;
    }

    recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
    cout << "UDP Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";

    std::system("pause");
}