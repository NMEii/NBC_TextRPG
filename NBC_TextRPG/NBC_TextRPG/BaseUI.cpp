#include "pch.h"
#include "BaseUI.h"

using namespace std;

BaseUI::BaseUI()
{
	canvasRect = GetCenteredRect(90, 30);

	titleRect = GetCenteredRect(90, 5);
	titleRect.y -= 12;
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
bool BaseUI::HandleKeyInput(int& index, int range)
{
	int input = _getch();

	// 방향키 일 경우에는 
	// input이 두번 들어옴. 
	if (input == 224 || input == 0)
	{
		input = _getch();
	}

	switch (static_cast<Key>(input))
	{
	case Key::Up:
		if (index > 0)
			index--;
		break;
	case Key::Down:
		if (index < range - 1)
			index++;
		break;
	case Key::Right:
		break;

	case Key::Left:
		break;

	case Key::Enter: return true; break; // Enter인 경우에만 true 
	}

	return false;
}

void BaseUI::Move(Pos TargetPos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = TargetPos.x;
	pos.Y = TargetPos.y;

	SetConsoleCursorPosition(handle, pos);
}

void BaseUI::ClearConsole()
{
	system("cls");
}

void BaseUI::GetConsoleSize(int& width, int& height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void BaseUI::SetCursorPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

UIRect BaseUI::GetCenteredRect(int boxW, int boxH)
{
	int consoleW, consoleH;
	GetConsoleSize(consoleW, consoleH);

	UIRect r;
	r.width = boxW;
	r.height = boxH;
	r.x = (consoleW - boxW) / 2;
	r.y = (consoleH - boxH) / 2;

	return r;
}

void BaseUI::DrawRect(const UIRect r)
{
	// 상단
	SetCursorPos(r.x, r.y);
	cout << "┌" << string(r.width - 2, '-') << "┐";

	// 중간
	for (int i = 1; i < r.height - 1; i++)
	{
		SetCursorPos(r.x, r.y + i);
		cout << "│" << string(r.width - 2, ' ') << "│";
	}

	// 하단
	SetCursorPos(r.x, r.y + r.height - 1);
	cout << "└" << string(r.width - 2, '-') << "┘";
}



