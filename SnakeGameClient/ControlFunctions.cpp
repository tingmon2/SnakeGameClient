#include "stdafx.h"
#include "SendFunctions.h"
#include <list>
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <list>
#include <WinSock2.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27

BOOL CtrlHandler(DWORD dwType)
{
	switch (dwType)
	{
		case CTRL_C_EVENT: // FORCE DISCONNECT
			return TRUE;
			break;
		case KEY_RIGHT: // TURN SNAKE RIGHT
			return TRUE;
			break;
		case KEY_LEFT: // TURN SNAKE RIGHT
			return TRUE;
			break;
		case KEY_UP: // TURN SNAKE RIGHT
			return TRUE;
			break;
		case KEY_DOWN: // TURN SNAKE RIGHT
			return TRUE;
			break;
		case ENTER: // RESUME GAME?
			return TRUE;
			break;
		case ESC: // STOP GAME?
			return TRUE;
			break;
		default:
			break;
	}
	return FALSE;
}