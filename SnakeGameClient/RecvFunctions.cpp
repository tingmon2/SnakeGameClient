#include "stdafx.h"
#include "RecvFunctions.h"
#include "SendFunctions.h"

void ClearConsole()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

std::string AskUserName()
{
    std::string userName;
    ClearConsole();
    printf("********** TCP Snake ************\n");
    printf("Please enter your name: ");
    std::getline(std::cin, userName);
    return userName;
}

void PopulateMainMenu(SOCKET hSocket, std::string username)
{
    char szBuffer[128] = { 0 };
    ClearConsole();
    printf("********** TCP Snake ************\n");
    printf("%s\n", username.c_str());
    printf("Please enter menu number.\n");
    printf("1. Play Game\n2. Watch Score\n3. Exit\n");
    gets_s(szBuffer);
    if (strcmp(szBuffer, "1") == 0)
    {
        SendGameMode(hSocket);
    }
    else if (strcmp(szBuffer, "2") == 0)
    {
        SendScoreMode(hSocket);
    }
    else if (strcmp(szBuffer, "3") == 0)
    {
        SendExitReq(hSocket);
    }
    else
    {

    }
}

void PopulateModeMenu()
{

}

void ShowMode()
{

}

void StartGame()
{

}
