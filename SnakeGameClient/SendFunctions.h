#pragma once
void SendPong(SOCKET hSocket);
void SendUserName(SOCKET hSocket, std::string userName);
void SendGameMode(SOCKET hSocket);
void SendScoreMode(SOCKET hSocket);
void SendExitReq(SOCKET hSocket);
