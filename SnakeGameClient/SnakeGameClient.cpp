#include "stdafx.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include "AppProtocol.h"
#include <Ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "SendFunctions.cpp"
#include "RecvFunctions.cpp"
#pragma comment(lib, "ws2_32")

int g_userDomain; // 0 - menu domain, 1- score domain, 2 - game domain
int g_userConnection; // 0 - unhealthy, 1 - healthy
int g_inGameStatus; // 0 - dead, 1 - alive
int g_snakeDirection;

void ErrorHandler(const char* pszMessage)
{
	printf("ERROR: %s\n", pszMessage);
	::WSACleanup();
	exit(1);
}

DWORD WINAPI GameThreadFunction(LPVOID pParam, int mode)
{
	int score;

}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa = { 0 }; 
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0) 
		ErrorHandler("Winsock Initialisation Failed."); 

	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0); 
	if (hSocket == INVALID_SOCKET) 
		ErrorHandler("Listening Socket Creating Failed."); 

	SOCKADDR_IN	svrAddr = { 0 }; // server address
	svrAddr.sin_family = AF_INET; // IPv4
	svrAddr.sin_port = htons(25000); // port number 250000
	InetPton(AF_INET, _T("127.0.0.1"), &svrAddr.sin_addr.s_addr);
	if (::connect(hSocket, (SOCKADDR*)&svrAddr, sizeof(svrAddr)) == SOCKET_ERROR)
		ErrorHandler("ERROR: Can not connect to server. The server may not listening.");
	puts("You have connected to the server."); 
	fflush(stdout); 

	g_userConnection = HEALTHY;
	g_userDomain = MENU_DOMAIN;
	g_inGameStatus = DEAD;
	 
	// 일단 while(1)로 계속 받게하고 그 다음에 리스닝 스레드 만들어야 할 듯??
	char szBuffer[128] = { 0 }; // buffer size
	while (1)
	{
		PACKET packet;
		if (::recv(hSocket, (char*)&packet, sizeof(PACKET), 0) > 0)
		{
			switch (packet.opcode)
			{
				case C_RECV_ERROR:
					ErrorHandler("UNKOWN ERROR");
					break;
				case C_RECV_PING:
					SendPong(hSocket);
					break;
				case C_RECV_TERMINATE_CONNECTION:
					g_userConnection = UNHEALTHY;
					break;
				case C_RECV_ACCEPT_CONNECTION:
					g_userConnection = HEALTHY;
					PopulateMainMenu();
					break;
				case C_RECV_SHOW_GAME_MODE:
					g_userDomain = MENU_DOMAIN;
					break;
				case C_RECV_SHOW_SCORE_MODE:
					g_userDomain = MENU_DOMAIN;
					break;
				case C_RECV_SHOW_SCORE:
					// show recieved score text
					break;
				case C_RECV_BACK_TO_MAIN:
					g_userDomain = MENU_DOMAIN;
					PopulateMainMenu();
					break;
				case C_RECV_GAME_START:
					g_userDomain = IN_GAME_DOMAIN;
					// create game thread??
					break;
				case C_RECV_MOVE_INFO:
					break;
				case C_RECV_CHANGE_DIRECTION:
					break;
				case C_RECV_NEW_TAIL_POPULATE:
					break;
				case C_RECV_NEW_TAIL_APPEND:
					break;
				case C_RECV_SNAKE_DEAD:
					g_inGameStatus = DEAD;
					// save score 
					// stop game thread?
					// enter => back to menu
					break;
				default:
					ErrorHandler("ERROR: OPCODE INVALID");
					break;
			}
		}
		if (g_userConnection == UNHEALTHY)
			break;
	}

	// close listen socket
	::closesocket(hSocket);
	// discharge winsock
	::WSACleanup();
	return 0;
}
