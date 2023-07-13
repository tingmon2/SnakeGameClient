#include "stdafx.h"
#include "RecvFunctions.h"
#include "SendFunctions.h"
#include "ControlFunctions.h"

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

DWORD WINAPI RecvThreadFunction(LPVOID pParam)
{
	SOCKET hSocket = (SOCKET)pParam;
	PACKET packet;
	while (::recv(hSocket, (char*)&packet, sizeof(PACKET), 0) > 0)
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
	return 0;
}

DWORD WINAPI SendThreadFunction(LPVOID pParam)
{
	SOCKET hSocket = (SOCKET)pParam;
	char szBuffer[128] = { 0 }; // buffer size
	gets_s(szBuffer);

	//g_userConnection = HEALTHY;
	//g_userDomain = MENU_DOMAIN;
	//g_inGameStatus = DEAD;
	//g_snakeDirection;

	switch (g_userDomain)
	{
	case MENU_DOMAIN:
		// 1. game play, 2. score, 3. exit
		break;
	case SCORE_DOMAIN:
		// 1. 15, 2. 20 3. back to main
		break;
	case GAME_DOMAIN:
		// 1. 15, 2. 20 3. back to main
		break;
	case IN_GAME_DOMAIN:
		// ??
		break;
	default:
		break;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa = { 0 }; 
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0) 
		ErrorHandler("Winsock Initialisation Failed."); 

	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0); 
	if (hSocket == INVALID_SOCKET) 
		ErrorHandler("Listening Socket Creating Failed."); 

	if (::SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE) == FALSE)
	{
		ErrorHandler("Can not register console control handler."); 
	}

	SOCKADDR_IN	svrAddr = { 0 }; // server address
	svrAddr.sin_family = AF_INET; // IPv4
	svrAddr.sin_port = htons(25000); // port number 250000
	InetPton(AF_INET, _T("127.0.0.1"), &svrAddr.sin_addr.s_addr);
	if (::connect(hSocket, (SOCKADDR*)&svrAddr, sizeof(svrAddr)) == SOCKET_ERROR)
		ErrorHandler("Can not connect to server. The server may not on service.");
	puts("You have connected to the server."); 
	fflush(stdout); 

	g_userConnection = HEALTHY;
	g_userDomain = MENU_DOMAIN;
	g_inGameStatus = DEAD;
	 
	// 일단 while(1)로 계속 받게하고 그 다음에 리스닝 스레드 만들어야 할 듯??
	while (1)
	{
		if (g_userConnection == UNHEALTHY)
			break;

		DWORD recvThreadID = 0; 
		HANDLE recvThread = CreateThread( 
			NULL,
			0,
			RecvThreadFunction,
			(LPVOID)hSocket,
			0,
			&recvThreadID);
		::CloseHandle(recvThread);

		DWORD sendThreadID = 0;
		HANDLE sendThread = CreateThread(
			NULL,
			0,
			SendThreadFunction,
			(LPVOID)hSocket,
			0,
			&sendThreadID);
		::CloseHandle(sendThread);
	}

	// close listen socket
	::closesocket(hSocket);
	// discharge winsock
	::WSACleanup();
	return 0;
}
