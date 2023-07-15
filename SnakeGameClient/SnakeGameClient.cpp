#include "stdafx.h"
#include "RecvFunctions.h"
#include "SendFunctions.h"
#include "ControlFunctions.h"

int g_userDomain; // 0 - menu domain, 1- score domain, 2 - game domain
int g_userConnection; // 0 - unhealthy, 1 - healthy
int g_inGameStatus; // 0 - dead, 1 - alive
int g_snakeDirection;
std::string g_userName;

void ErrorHandler(const char* pszMessage)
{
	printf("ERROR: %s\n", pszMessage);
	::WSACleanup();
	exit(1);
}

void CreateFrame()
{
	for (int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 50; b++)
		{
			if (a == 0 || a == 19) {
				printf("#");
			}
			else if (b == 0 || b == 49)
			{
				printf("#");
			}
			else
			{
				printf(" ");
			}

		}
		printf("\n");
	}
	g_snakeDirection = RIGHT;
}

DWORD WINAPI RecvThreadFunction(LPVOID pParam)
{
	SOCKET hSocket = (SOCKET)pParam;
	PACKET packet;
	packet.opcode = 0;
	packet.data = "";
	while (::recv(hSocket, (char*)&packet, sizeof(PACKET), 0) > 0)
	{
		if (packet.opcode < 700)
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
					g_userName = AskUserName();
					SendUserName(hSocket, g_userName);
					PopulateMainMenu(hSocket, g_userName);
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
					PopulateMainMenu(hSocket, g_userName);
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
	}
	Sleep(200);
	return 0;
}

DWORD WINAPI SendThreadFunction(LPVOID pParam)
{
	SOCKET hSocket = (SOCKET)pParam;
	char szBuffer[128] = { 0 }; // buffer size
	while (1)
	{
		if (g_userDomain == IN_GAME_DOMAIN) {
			switch (g_snakeDirection)
			{
			case RIGHT:
				break;
			case LEFT:
				break;
			case UP:
				break;
			case DOWN:
				break;
			default:
				break;
			}
			Sleep(500);
		}
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

	while (1)
	{
		if (g_userConnection == UNHEALTHY)
			break;
	}

	// close listen socket
	::closesocket(hSocket);
	// discharge winsock
	::WSACleanup();
	return 0;
}
