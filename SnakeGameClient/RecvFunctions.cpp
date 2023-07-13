#include "stdafx.h"
#include "RecvFunctions.h"

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

void PopulateMainMenu()
{
    ClearConsole();
    printf("********** TCP Snake ************\n");
    printf("Please enter menu number.\n");
    printf("1. Play Game\n2. Watch Score\n3. Exit\n");
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
