#include "stdafx.h"
#include "SendFunctions.h"
#include "RecvFunctions.h"

void SendPong(SOCKET hSocket)
{
	PACKET packet;
	packet.opcode = C_SEND_PONG;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}

void SendUserName(SOCKET hSocket, std::string userName)
{
	PACKET packet;
	packet.opcode = C_SEND_USER_NAME_INFO;
	packet.data = userName;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}

void SendGameMode(SOCKET hSocket)
{
	PACKET packet;
	packet.opcode = C_SEND_GAME_START_REQ;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}

void SendScoreMode(SOCKET hSocket)
{
	PACKET packet;
	packet.opcode = C_SEND_SCORE_MODE_SELECT;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}

void SendExitReq(SOCKET hSocket)
{
	PACKET packet;
	packet.opcode = C_SEND_EXIT;
	send(hSocket, (const char*)&packet, sizeof(packet), 0);
}