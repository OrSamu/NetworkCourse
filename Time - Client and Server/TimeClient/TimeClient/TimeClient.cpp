#include "clientUtils.h"

void main()
{
	// Initialize Winsock (Windows Sockets).

	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "UDP Client: Error at WSAStartup()\n";
		return;
	}

	// Client side:
	// Create a socket and connect to an internet address.

	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		std::cout << "UDP Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// For a client to communicate on a network, it must connect to a server.
	// Need to assemble the required data for connection in sockaddr structure.
	// Create a sockaddr_in object called server. 

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);

	// Initialize variables
	int bytesSent;
	int bytesRecv;
	char sendBuff[255];
	char recvBuff[255];
	bool keepClientAlive = true;
	bool soloRequest;
	bool waitForClearingScreen = true;

	while (keepClientAlive)
	{
		int usersRequest = getUserRequest();

		sprintf_s(sendBuff, "%d", usersRequest);
		soloRequest = false;
		switch (usersRequest)
		{
		case 0:
			keepClientAlive = false;
			closeClient();
			break;
		case 4:
			getClientToServerDelayEstimation(connSocket, sendBuff, recvBuff, server, bytesSent, bytesRecv);
			break;
		default :
			sendSimpleRequest(connSocket, sendBuff, recvBuff, server, bytesSent, bytesRecv);
			break;
		}
	}

	// Closing connections and Winsock.
	std::cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	std::system("pause");
}