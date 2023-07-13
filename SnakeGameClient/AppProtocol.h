#pragma once
#include <string>

typedef enum USERLOCATION {
	MENU_DOMAIN = 0,
	SCORE_DOMAIN = 1,
	GAME_DOMAIN = 2,
	IN_GAME_DOMAIN = 3
} USERLOCATION;

typedef enum USERCONNECTION {
	UNHEALTHY = 0,
	HEALTHY = 1
} USERCONNECTION;

typedef enum INGAMESTATUS {
	DEAD = 0,
	ALIVE = 1
} INGAMESTATUS;

typedef enum GAMEMODE {
	FIFTEEN = 15,
	TWENTY = 20
} GAMEMODE;

typedef enum RECV_OPCODE {
	C_RECV_ERROR = 51,
	C_RECV_PING = 52,
	C_RECV_ACCEPT_CONNECTION = 53,
	C_RECV_TERMINATE_CONNECTION = 54,

	C_RECV_SHOW_GAME_MODE = 500,
	C_RECV_SHOW_SCORE_MODE = 501,
	C_RECV_SHOW_SCORE = 502,
	C_RECV_BACK_TO_MAIN = 503,

	C_RECV_GAME_START = 600, // WAIT 3 SEC THEN GAME START
	C_RECV_MOVE_INFO = 601, // SEND NEW COORDINATE OF SNAKE HEAD
	C_RECV_CHANGE_DIRECTION = 602,
	C_RECV_NEW_TAIL_POPULATE = 603, // NEW TAIL POPULATE ON THE MAP - MAXIMUM 3
	C_RECV_NEW_TAIL_APPEND = 604, // NEW SNAKE TAIL IS ON THE NEW COORDINATE, APPEND IT
	C_RECV_SNAKE_DEAD = 605 // NEW COORDINATE INDICATED COLLISION

} RECV_OPCODE;

typedef enum SEND_OPCODE {
	C_SEND_ERROR = 1,
	C_SEND_PONG = 2,
	C_SEND_EXIT = 3,

	C_SEND_USER_NAME_INFO = 100, // ASK USER NAME AFTER CONNECTION ESTABLISHED
	C_SEND_MAIN_MENU_SELECT = 101, // MAIN MENU 1. GAME PLAY, 2. SHOW SCORE, 3. EXIT
	C_SEND_GAME_MODE_SELECT = 102, // GAME MODE 1. 15X15, 2. 20X20
	C_SEND_SCORE_MODE_SELECT = 103, // SCORE MODE 1. 15X15, 2. 20X20

	C_SEND_TURN_RIGHT = 200,
	C_SEND_TURN_LEFT = 201,
	C_SEND_TURN_UP = 202,
	C_SEND_TURN_DOWN = 203
} SEND_OPCODE;

/////////////////////////////////////////////////////////////////////////
//기본헤더
typedef struct PACKET
{
	int opcode;			// opcode
	std::string Data;	// packet data
} PACKET;

/////////////////////////////////////////////////////////////////////////
//확장헤더: 에러 메시지 전송헤더
typedef struct ERRORDATA
{
	int	nErrorCode;		//에러코드: ※향후 확장을 위한 멤버다.
	char szDesc[256];	//에러내용
} ERRORDATA;

/////////////////////////////////////////////////////////////////////////
//확장헤더: S->C: 파일 리스트 전송
typedef struct SEND_FILELIST
{
	unsigned int nCount;	//전송할 파일정보(GETFILE 구조체) 개수
} SEND_FILELIST;

/////////////////////////////////////////////////////////////////////////
//확장헤더: CMD_GET_FILE
typedef struct GETFILE
{
	unsigned int nIndex;	//전송받으려는 파일의 인덱스
} GETFILE;

/////////////////////////////////////////////////////////////////////////
//확장헤더: 
typedef struct FILEINFO
{
	unsigned int nIndex;			//파일의 인덱스
	char szFileName[_MAX_FNAME];	//파일이름
	DWORD dwFileSize;				//파일의 바이트 단위 크기
} FILEINFO;

