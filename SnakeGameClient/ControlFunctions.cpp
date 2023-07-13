#include "stdafx.h"
#include "SendFunctions.h"
#include <list>
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <list>
#include <WinSock2.h>

BOOL CtrlHandler(DWORD dwType)
{
	if (dwType == CTRL_C_EVENT)
	{
		//std::list<SOCKET>::iterator it;

		//::shutdown(g_hSocket, SD_BOTH); // block request

		//::EnterCriticalSection(&g_cs);
		//for (it = g_clientList.begin(); it != g_clientList.end(); it++)
		//{
		//	::closesocket(*it);
		//}
		//g_clientList.clear();
		//g_clientHealthList.clear();
		//::LeaveCriticalSection(&g_cs);

		//puts("Disconnect all clients and closing server...");
		//// this kind of waiting is not good for data critical server.
		//// for example, MMORPG server must save every info before closure.
		//::Sleep(100); // wait until all client connection close

		//DeleteCriticalSection(&g_cs);
		//::closesocket(g_hSocket);
		//::WSACleanup();
		//exit(0);
		//return TRUE;
	}
	return FALSE;
}