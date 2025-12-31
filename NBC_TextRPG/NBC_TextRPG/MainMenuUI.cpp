#include "pch.h"
#include "MainMenuUI.h"

using namespace std; 

MainMenuUI::MainMenuUI()
{
	menus = 
	{ 
		"게임 시작", 
		"게임 종료"
	};


	menuRect = GetCenteredRect(60, 8);

	KeyRect = GetCenteredRect(60, 4);
	KeyRect.y += 9;
}

MainMenuUI::~MainMenuUI()
{
}

void MainMenuUI::Render()
{
	ClearConsole();

	DrawRect(canvasRect);
	DrawRect(titleRect);
	DrawRect(KeyRect);


	SetCursorPos(titleRect.InnerX() + 26, titleRect.InnerY()+1);
	cout << "병권몬스터";
	
	for (int i = 0; i < menus.size(); i++)
	{
		SetCursorPos(menuRect.x + 22, menuRect.y+7 + i*2);
		if (i == selectedIndex)
		{
			cout << "  ▶ " << "[" << menus[i] << "]";
		}
			
		else
		{
			cout << "    " << menus[i];
		}
	}


	SetCursorPos(KeyRect.x + 10, KeyRect.y + 1);
	cout << "↑↓ 이동 / ENTER 선택";

}

void MainMenuUI::Update()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex);
	}
}

void MainMenuUI::OnSelect(int choice)
{
	// 예시 
	if (choice == 0 && OnRequest)
		OnRequest(UIRequest::OpenCombatUI);
	
	if (choice == 1 && OnRequest)
		OnRequest(UIRequest::ExitGame);
}

 
