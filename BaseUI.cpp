#include "pch.h"
#include "BaseUI.h"

using namespace std;

int BaseUI::HandleInput(int range)
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
