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
bool BaseUI::HandleKeyInput(Pos& pos, const std::pair<Pos, Pos> range)
{
	int input = _getch();

	// 방향키 일 경우에는 
	// input이 두번 들어옴. 
	if (input == 224 || input == 0)
	{
		input = _getch();  
	}

	// 다음 좌표 
	int nextx = pos.x, nexty = pos.y;

	switch (static_cast<Key>(input))
	{
	case Key::Up: nexty--; break; 

	case Key::Down: nexty++; break; 

	case Key::Right: nextx++; break;

	case Key::Left: nextx--; break; 

	case Key::Enter: return true; break; // Enter인 경우에만 true 
	}

	// 범위 이탈 체크 
	if (nextx >= range.first.x && nextx <= range.second.x &&
		nexty >= range.first.y && nexty <= range.second.y)
	{
		pos.x = nextx;
		pos.y = nexty;
	}

	return false; 
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

