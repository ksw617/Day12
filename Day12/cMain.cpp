#include <stdio.h>
#include <Windows.h>

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

int main()
{
	InitBuffer();

	while (true)
	{
		//printf("Hello world");
		WriteBuffer(10, 10, "Hello world", LIGHTMAGENTA);
		//Todo

		FlipBuffer();
		ClearBuffer();

		Sleep(50);
	}
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
