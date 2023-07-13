#include "stdafx.h"
#include "SendFunctions.h"

void SendPong(SOCKET hSocket)
{
	PACKET packet;
	packet.opcode = C_SEND_PONG;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}