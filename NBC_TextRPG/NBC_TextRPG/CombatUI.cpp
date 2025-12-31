#include "pch.h"
#include "CombatUI.h"

CombatUI::CombatUI()
{
	menus =
	{
		"싸운다",
		"인벤토리",
		"상점",
		"나가기",
	};

	// 예시 
	skills =
	{
		"할퀴기",
		"몸통박치기",
		"울음소리",
		"나가기"
	};
	

}

CombatUI::~CombatUI()
{
}

void CombatUI::Render()
{ 
	ClearConsole();

	canvasRect = GetCenteredRect(60, 18);

	titleRect = canvasRect; 
	titleRect.height = 5;
	titleRect.y = canvasRect.y - titleRect.height+1; 


	scriptRect = GetCenteredRect(40, 6);
	scriptRect.x -= 10;
	scriptRect.y += 7;

	menuRect = GetCenteredRect(20, 6);
	menuRect.x += 20;
	menuRect.y += 7;

	DrawRect(canvasRect);

	DrawRect(titleRect);	

	SetCursorPos(titleRect.InnerX() + 26, titleRect.InnerY() + 1);
	cout << "전투";

	DrawScriptRect(); 
	
	DrawMenuRect(); 
}

void CombatUI::Update()
{
	switch (currentState)
	{
	case CombatUIState::Command:

		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}

		break;

	case CombatUIState::SkillSelect:
		if (HandleKeyInput(selectedSkillIndex, skills.size()))
		{
			// 싸움 로직 
			switch (selectedSkillIndex)
			{
			case 0:
				// 할퀴기  

				break;

			case 1:
				// 몸통박치기  

				break;

			case 2:
				// 울음 소리 
				break;

			case 3:
				// 나가기 
				currentState = CombatUIState::Command;
				break;
			}

		}
		break;

	case CombatUIState::Result:

		break;


	}


}

void CombatUI::OnSelect(int choice)
{
	if (choice == 0 ) // 싸운다 
	{
		currentState = CombatUIState::SkillSelect;
	}

	if (choice == 1 && OnRequest) // 인벤토리 
	{
		OnRequest(UIRequest::OpenInventoryUI);
	}
	if (choice == 2 && OnRequest) // 상점 
	{
		OnRequest(UIRequest::OpenStoreUI);
	}
	if (choice == 3 && OnRequest) // 나가기 
	{
		OnRequest(UIRequest::OpenMainMenu);
	}

}


void CombatUI::DrawMenuRect()
{
	DrawRect(menuRect);

	switch (currentState)
	{
	case CombatUIState::Command:
		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY() + i);
			if (i == selectedIndex)
			{
				cout << "  ▶ " << "[" << menus[i] << "]";
			}

			else
			{
				cout << "    " << menus[i];
			}
		}

		break; 

	case CombatUIState::SkillSelect:

		for (int i = 0; i < skills.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY() + i);
			if (i == selectedSkillIndex)
			{
				cout << "  ▶ " << "[" << skills[i] << "]";
			}

			else
			{
				cout << "    " << skills[i];
			}
		}

		break; 
	}
}

void CombatUI::DrawScriptRect()
{
	DrawRect(scriptRect);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

	switch (currentState)
	{
	case CombatUIState::Command :
		cout << "무엇을 하지?"; 
		break; 

	case CombatUIState::SkillSelect:
		cout << "선택";
		break; 

	case CombatUIState::Result:
		// 싸움 스크립트... 

		break; 
	}

	

}
