#include <stdio.h>
#include <Windows.h>

#pragma region Enum
enum Scene_ID
{
	LOGO,
	MENU,
	STAGE,
};
#pragma endregion


#pragma region Struct

struct Obj
{
	int x;
	int y;
	const char* shape;
};

#pragma endregion

Scene_ID id;

#pragma region Logo
const char* logoImg[13];

void LogoInitialize();
void LogoProgress();
void LogoRender();
void LogoRelease();
#pragma endregion

#pragma region Menu
const char* menuImg[8];

int menuIndex;

Obj* arrowText = nullptr;
Obj* startText = nullptr;
Obj* optionText = nullptr;
Obj* exitText = nullptr;

void MenuInitialize();
void MenuProgress();
void MenuRender();
void MenuRelease();
#pragma endregion

#pragma region WinAPI
void MoveCursorPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
#pragma endregion



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
			MenuProgress();
			MenuRender();
			break;
		case STAGE:
			printf("STAGE\n");
			break;
		default:
			break;
		}

		Sleep(50);
	}
}

#pragma region Logo
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
		MenuInitialize();
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

#pragma endregion
#pragma region Menu
void MenuInitialize()
{
	 menuImg[0] = "'##::::'##:'########:'##::: ##:'##::::'##:";
	 menuImg[1] = " ###::'###: ##.....:: ###:: ##: ##:::: ##:";
	 menuImg[2] = " ####'####: ##::::::: ####: ##: ##:::: ##:";
	 menuImg[3] = " ## ### ##: ######::: ## ## ##: ##:::: ##:";
	 menuImg[4] = " ##. #: ##: ##...:::: ##. ####: ##:::: ##:";
	 menuImg[5] = " ##:.:: ##: ##::::::: ##:. ###: ##:::: ##:";
	 menuImg[6] = " ##:::: ##: ########: ##::. ##:. #######::";
	 menuImg[7] = "..:::::..::........::..::::..:::.......:::";

	 arrowText = (Obj*)malloc(sizeof(Obj));
	 arrowText->x = 10;
	 arrowText->y = 20;
	 arrowText->shape = "¢º";

	 startText = (Obj*)malloc(sizeof(Obj));
	 startText->x = 15;
	 startText->y = 20;
	 startText->shape = "START";

	 optionText = (Obj*)malloc(sizeof(Obj));
	 optionText->x = 15;
	 optionText->y = 22;
	 optionText->shape = "OPTION";

	 exitText = (Obj*)malloc(sizeof(Obj));
	 exitText->x = 15;
	 exitText->y = 24;
	 exitText->shape = "EXIT";

}


void MenuProgress()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (arrowText->y > startText->y)
		{
			arrowText->y -= 2;
			menuIndex--;
		}

	}
	if (GetAsyncKeyState(VK_DOWN))
	{

		if (arrowText->y < exitText->y)
		{
			arrowText->y += 2;
			menuIndex++;
		}
		
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (menuIndex)
		{
		case 0:
			id = STAGE;
			MenuRelease();
			break;

		case 2:
		//	exit(true);
			break;
		default:
			break;
		}
	}
}

void MenuRender()
{
	if (id == STAGE)
	{
		return;
	}

	for (int i = 0; i < 8; i++)
	{
		MoveCursorPosition(5, 5 + i);
		printf(menuImg[i]);
	}

	MoveCursorPosition(arrowText->x , arrowText->y);
	printf(arrowText->shape);

	MoveCursorPosition(startText->x, startText->y);
	printf(startText->shape);

	MoveCursorPosition(optionText->x, optionText->y);
	printf(optionText->shape);

	MoveCursorPosition(exitText->x, exitText->y);
	printf(exitText->shape);
}

void MenuRelease()
{
	if (arrowText != nullptr)
	{
		free(arrowText);
		arrowText = nullptr;
	}

	if (startText != nullptr)
	{
		free(startText);
		startText = nullptr;
	}

	if (optionText != nullptr)
	{
		free(optionText);
		optionText = nullptr;
	}

	if (exitText != nullptr)
	{
		free(exitText);
		exitText = nullptr;
	}
}
#pragma endregion



