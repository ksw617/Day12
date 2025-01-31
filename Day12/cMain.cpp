#include <stdio.h>
#include <Windows.h>

#pragma region DoubleBuffer
//���� �ʱ�ȭ
#define BufferWidth 80	// ���� ���� ũ��
#define BufferHeight 40 // ���� ���� ũ��


HANDLE hBuffer[2];	//â �ΰԸ� �����ϴ� �ڵ�
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
		bullets[i]->shape = "��";
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
//���� �ʱ�ȭ
void InitBuffer()
{
	//���� ��ũ�� index���� 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : ȭ�� ũ��
	COORD size = { BufferWidth, BufferHeight };

	//â ũ�� ���� : 0, ���� : 0 ������ : 80 - 1, �Ʒ��� : 40 - 1
	SMALL_RECT rect = { 0,0,BufferWidth - 1, BufferHeight - 1 };

	//0�� ���� �����
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0�� ȭ�� ���� ������ ����(���� ���� �ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0�� â ������ ����
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1�� ���� �����
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1�� ȭ�� ���� ������ ����(���� ���� �ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1�� â ������ ����
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO info;	//�ܼ� Ŀ�� ���� ����ü
	info.dwSize = 1;			//Ŀ�� ũ��
	info.bVisible = FALSE;		//Ŀ�� �Ⱥ��̰�

	//0 & 1 ������ ���ۿ� Ŀ�� ���� ���
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}


//���� ������ 0->1 1->0 
void FlipBuffer()
{
	//�ش� ���� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0]->[1] / [1]->[0]
	screenIndex = !screenIndex;
}

//���� â ������
void ClearBuffer()
{
	//���� ��ġ
	//pos.x = 0; pos.y = 0;
	COORD pos = { 0,0 };
	//�Ű����� �� �־��ٷ���
	DWORD dw;

	//ȭ���� ' '�� ä��
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}


//���ڿ� ���ϴ� ��ġ�� ���ֱ� & ���� ����
//WriteBuffer(x��ǥ, y��ǥ, ���ڿ�, ���� �ε���)
void WriteBuffer(int x, int y, const char* shape, int color)
{
	//��ġ ����
	//pos.x = x * 2; pos.y = y;
	COORD pos = { x * 2, y };

	//Ŀ�� ��ġ �̵�
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);

	//���� �ٲ��ֱ�
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//�Ű����� ���� �ֱ� ����
	DWORD dw;

	//�ش� ���ۿ� ����
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

//���� ����
void CloseBuffer()
{
	//���� �ݱ�
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#pragma endregion
