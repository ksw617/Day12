#include <stdio.h>
#include <Windows.h>

#pragma region DoubleBuffer
//버퍼 초기화
#define BufferWidth 80	// 가로 버퍼 크기
#define BufferHeight 40 // 세로 버퍼 크기


HANDLE hBuffer[2];	//창 두게를 제어하는 핸들
int screenIndex;	//hBuffer[screenIndex], screenIndex == 0 or 1


void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void CloseBuffer();

#pragma endregion
#pragma region Enum
enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,
};

#pragma endregion

struct Obj
{
	int aniIndex;
	int x;
	int y;
	Color color;
	const char* shape[10][3];

};

#define BulletCount 10

struct Bullet
{
	bool act;
	int x;
	int y;
	Color color;
	const char* shape;

};


Obj* player = nullptr;
Bullet* bullets[BulletCount] = {};


int main()
{
	InitBuffer();


	player = (Obj*)malloc(sizeof(Obj));
	player->aniIndex = 0;
	player->x = 10;
	player->y = 10;
	player->color = YELLOW;
	player->shape[0][0] = "   -----|-----";
	player->shape[0][1] = "*>=====[_]L)";
	player->shape[0][2] = "      -'-`-";

	player->shape[1][0] = "    ----|---- ";
	player->shape[1][1] = "*>=====[_]L)";
	player->shape[1][2] = "      -'-`-";

	player->shape[2][0] = "     ---|---";
	player->shape[2][1] = "*>=====[_]L)";
	player->shape[2][2] = "      -'-`-";

	player->shape[3][0] = "      --|--";
	player->shape[3][1] = "*>=====[_]L)";
	player->shape[3][2] = "      -'-`-";

	player->shape[4][0] = "       ---";
	player->shape[4][1] = "*>=====[_]L)";
	player->shape[4][2] = "      -'-`-";

	player->shape[5][0] = "        -";
	player->shape[5][1] = "*>=====[_]L)";
	player->shape[5][2] = "      -'-`-";

	player->shape[6][0] = "       ---";
	player->shape[6][1] = "*>=====[_]L)";
	player->shape[6][2] = "      -'-`-";

	player->shape[7][0] = "      --|--";
	player->shape[7][1] = "*>=====[_]L)";
	player->shape[7][2] = "      -'-`-";

	player->shape[8][0] = "     ---|---";
	player->shape[8][1] = "*>=====[_]L)";
	player->shape[8][2] = "      -'-`-";

	player->shape[9][0] = "    ----|---- ";
	player->shape[9][1] = "*>=====[_]L)";
	player->shape[9][2] = "      -'-`-";


	for (int i = 0; i < BulletCount; i++)
	{
		bullets[i] = (Bullet*)malloc(sizeof(Bullet));
		bullets[i]->act = false;
		bullets[i]->x = i;
		bullets[i]->y = 0;
		bullets[i]->shape = "●";
		bullets[i]->color = MAGENTA;
	}



	while (true)
	{

		if (GetAsyncKeyState(VK_LEFT))
		{
			player->x--;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			player->x++;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			player->y--;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			player->y++;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{

			for (int i = 0; i < BulletCount; i++)
			{

				if (bullets[i]->act == false)
				{

					bullets[i]->x = player->x + 6;
					bullets[i]->y = player->y + 1;


					bullets[i]->act = true;
					break;

				}


			}

		}



		player->aniIndex++;
		player->aniIndex %= 10;
		
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(player->x, player->y + i, player->shape[player->aniIndex][i], player->color);
		}

		for (int i = 0; i < BulletCount; i++)
		{
			WriteBuffer(bullets[i]->x, bullets[i]->y, bullets[i]->shape, bullets[i]->color);
		}

		FlipBuffer();
		ClearBuffer();

		Sleep(50);
	}

	CloseBuffer();

	return 0;
}


#pragma region DoubleBuffer
//버퍼 초기화
void InitBuffer()
{
	//현재 스크린 index값은 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : 화면 크기
	COORD size = { BufferWidth, BufferHeight };

	//창 크기 왼쪽 : 0, 위쪽 : 0 오른쪽 : 80 - 1, 아래쪽 : 40 - 1
	SMALL_RECT rect = { 0,0,BufferWidth - 1, BufferHeight - 1 };

	//0번 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1번 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO info;	//콘솔 커서 정보 구조체
	info.dwSize = 1;			//커서 크기
	info.bVisible = FALSE;		//커서 안보이게

	//0 & 1 각각의 버퍼에 커서 정보 등록
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}


//버퍼 뒤집기 0->1 1->0 
void FlipBuffer()
{
	//해당 버퍼 활성화
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0]->[1] / [1]->[0]
	screenIndex = !screenIndex;
}

//버퍼 창 깨끗이
void ClearBuffer()
{
	//시작 위치
	//pos.x = 0; pos.y = 0;
	COORD pos = { 0,0 };
	//매개변수 값 넣어줄려고
	DWORD dw;

	//화면을 ' '로 채움
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}


//문자열 원하는 위치에 써주기 & 색깔 까지
//WriteBuffer(x좌표, y좌표, 문자열, 색깔 인덱스)
void WriteBuffer(int x, int y, const char* shape, int color)
{
	//위치 설정
	//pos.x = x * 2; pos.y = y;
	COORD pos = { x * 2, y };

	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);

	//색깔 바꿔주기
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//매개변수 값을 넣기 위해
	DWORD dw;

	//해당 버퍼에 쓰기
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

//버퍼 해제
void CloseBuffer()
{
	//버퍼 닫기
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#pragma endregion
