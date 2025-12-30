#include "pch.h"
#include "BaseUI.h"

using namespace std;

BaseUI::BaseUI()
{
}

BaseUI::~BaseUI()
{
}

// 숫자 키 입력받기 
int BaseUI::HandleInputByNums(int range)
{
	int input;

	while (true)
	{
		cin >> input; 
		if (cin.fail() || input < 0 || input > range)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "잘못된 값을 입력하셨습니다.\n > ";
		}
		else
		{
			break;
		}
	}

	return input;
}

// 키보드 입력(ESC, Enter, 방향키) 받기 
void BaseUI::HandleKeyInput(Pos& pos, const std::pair<Pos, Pos> Range)
{
	int input = _getch();
	int nextx, nexty;

	switch (input)
	{
	case UP:
		nexty = pos.y - 1;
		if (nexty >= Range.first.y && nexty <= Range.second.y)
			pos.y = nexty;

		break;

	case DOWN:
		nexty = pos.y + 1;
		if (nexty >= Range.first.y && nexty <= Range.second.y)
			pos.y = nexty;

		break;

	case RIGHT:
		nextx = pos.x + 1;
		if (nextx >= Range.first.x && nextx <= Range.second.x)
			pos.x = nextx;
		
		break;

	case LEFT:
		nextx = pos.x - 1; 
		if (nextx >= Range.first.x && nextx <= Range.second.x)
			pos.x = nextx;
		
		break;

	case Enter:

		break;
	}
}

void BaseUI::ClearConsole()
{
	system("cls"); 
}

// 
void BaseUI::Move(Pos TargetPos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = TargetPos.x;
	pos.Y = TargetPos.y;

	SetConsoleCursorPosition(handle, pos);
}

