#include <stdio.h>
#include <Windows.h>

enum Scene_ID
{
	LOGO,
	MENU,
	STAGE,
};

Scene_ID id;

const char* logoImg[13];

void LogoInitialize();
void LogoProgress();
void LogoRender();
void LogoRelease();

void MoveCursorPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int main()
{
	id = LOGO;
	LogoInitialize();

	while (true)
	{
		system("cls");

		switch (id)
		{
		case LOGO:
			LogoProgress();
			LogoRender();
			break;
		case MENU:
			printf("MENU\n");
			break;
		case STAGE:
			printf("STAGE\n");
			break;
		default:
			break;
		}

		Sleep(500);
	}
}

void LogoInitialize()
{
	logoImg[0] = "    ..........           @@@@@    @@@@@.......";
	logoImg[1] = "     .........          @     @  @     @.......";
	logoImg[2] = "      ........             @@@   @     @........";
	logoImg[3] = "       .......           @@      @     @  .......";
	logoImg[4] = "        ......          @@@@@@@   @@@@@  th ......";
	logoImg[5] = "         .....        ----------------------- .....";
	logoImg[6] = "          ....          C  E  N  T  U  R  Y     ....";
	logoImg[7] = "           ...        -----------------------     ...";
	logoImg[8] = "            ..        @@@@@ @@@@@ @   @ @@@@@       ..";
	logoImg[9] = "            ==          @   @      @ @    @          ==";
	logoImg[10] = "          __||__        @   @@@@    @     @        __||__";
	logoImg[11] = "         |      |       @   @      @ @    @       |      |";
	logoImg[12] = "_________|______|_____  @   @@@@@ @   @   @  _____|______|_________";

}



void LogoProgress()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		id = MENU;
		LogoRelease();
	}
}

void LogoRender()
{
	for (int i = 0; i < 13; i++)
	{
		MoveCursorPosition(5, 5 + i);
		printf(logoImg[i]);
	}
}

void LogoRelease()
{
}
