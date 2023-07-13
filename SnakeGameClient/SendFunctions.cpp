#include "stdafx.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include "AppProtocol.h"
#include <string>

void SendPong(SOCKET hSocket)
{
	OPCODE op;
	op.nCode = C_SEND_PONG;
	send(hSocket, (const char*)&op, sizeof(op), 0);
}