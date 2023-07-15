#pragma once
void ClearConsole();
std::string AskUserName();
void PopulateMainMenu(SOCKET hSocket, std::string username);
void PopulateModeMenu();
void ShowMode();
void StartGame();