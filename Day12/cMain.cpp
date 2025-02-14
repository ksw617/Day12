#include <stdio.h>
#include <Windows.h>
#include <time.h>

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
	int hp;
	int x;
	int y;
	Color color;
	const char* shape[10][3];

};

#define BulletCount 5

struct Bullet
{
	bool act;
	int x;
	int y;
	Color color;
	const char* shape;

};

enum ITEM_TYPE
{
	BULLET,
	HEART,
	SPEED,

	Item_Count,

};

struct Item
{
	bool act;
	ITEM_TYPE type;
	int x;
	int y;
	Color color;
	const char* shape;
};


Obj* player = nullptr;
Bullet* bullets[BulletCount] = {};
Item* items[Item_Count] = {};


int main()
{
	srand((unsigned)time(NULL));


	const int screenRight = BufferWidth / 2;
	InitBuffer();


	player = (Obj*)malloc(sizeof(Obj));
	player->aniIndex = 0;
	player->hp = 3;
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

	for (int i = 0; i < Item_Count; i++)
	{
		items[i] = (Item*)malloc(sizeof(Item));
		items[i]->act = false;
		items[i]->type = (ITEM_TYPE)i;
		items[i]->x = 0;
		items[i]->y = 0;
		items[i]->color = LIGHTGREEN;
		items[i]->shape = "▣";
	}

	//test
	items[1]->act = true;
	items[1]->x = screenRight - 1;
	items[1]->y = rand() % BufferHeight;


	while (true)
	{

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			player->x--;
			if (player->x < 0)
			{
				player->x = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			player->x++;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			player->y--;
			if (player->y < 1)
			{
				player->y = 1;
			}
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			player->y++;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
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

		for (int i = 0; i < BulletCount; i++)
		{
			if (bullets[i]->act)
			{
				bullets[i]->x++;

				if (bullets[i]->x >= screenRight)
				{
					bullets[i]->act = false;
					bullets[i]->x = i;
					bullets[i]->y = 0;
				}

			}
		}


		for (int i = 0; i < Item_Count; i++)
		{
			if (items[i]->act)
			{
				items[i]->x--;
				
				if (items[i]->x < 0)
				{
					items[i]->act = false;

				}

				if (player->x <= items[i]->x && items[i]->x < player->x + 7 &&
					player->y <= items[i]->y && items[i]->y < player->y + 3)
				{
					items[i]->act = false;
					switch (items[i]->type)
					{
					case BULLET:
						break;
					case HEART:
						player->hp++;
						break;
					case SPEED:
						break;
					default:
						break;

					}
				}

			}
		}


		player->aniIndex++;
		player->aniIndex %= 10;
		
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(player->x, player->y + i, player->shape[player->aniIndex][i], player->color);
		}

		for (int i = 1; i <= player->hp; i++)
		{
		
			WriteBuffer(screenRight - i, 0, "♥", LIGHTRED);
		}

		for (int i = 0; i < BulletCount; i++)
		{
			WriteBuffer(bullets[i]->x, bullets[i]->y, bullets[i]->shape, bullets[i]->color);
		}


		for (int i = 0; i < Item_Count; i++)
		{
			if (items[i]->act)
			{
				WriteBuffer(items[i]->x, items[i]->y, items[i]->shape, items[i]->color);
			}
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
