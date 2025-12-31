#include "pch.h"
#include "CombatUI.h"

CombatUI::CombatUI()
{
	menus =
	{
		"싸운다",
		"인벤토리",
		"나가기",
	};

	skills =
	{
		"할퀴기",
		"몸통박치기",
		"울음소리",
		"나가기"
	};
	
	scriptRect = GetCenteredRect(40, 6);
	scriptRect.x -= 10;
	scriptRect.y += 7;

	menuRect = GetCenteredRect(20, 6);
	menuRect.x += 20;
	menuRect.y += 7;
}

CombatUI::~CombatUI()
{
}

void CombatUI::Render()
{ 
	ClearConsole();

	DrawRect(canvasRect);

	DrawRect(TitleRect);	

	SetCursorPos(TitleRect.InnerX() + 26, TitleRect.InnerY() + 1);
	cout << "전투";

	DrawRect(scriptRect);
	DrawRect(menuRect);

	if (bShouldDrawMenu)
	{
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
	}
	else
	{
		for (int i = 0; i < skills.size(); i++)
		{
			SetCursorPos(menuRect.InnerX()+1, menuRect.InnerY() + i);
			if (i == selectedSkillIndex)
			{
				cout << "  ▶ " << "[" << skills[i] << "]";
			}

			else
			{
				cout << "    " << skills[i];
			}
		}

	}


	
}

void CombatUI::Update()
{
	if (bShouldDrawMenu)
	{
		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}
	}
	else
	{
		if (HandleKeyInput(selectedSkillIndex, skills.size()))
		{
			// 싸움 로직 
			switch (selectedSkillIndex)
			{
			case 0:

				break;

			case 1:
				break;

			case 2:
				break;

			case 3:
				bShouldDrawMenu = true; 
				break; 
			}

		}
	}
	
	

}

void CombatUI::OnSelect(int choice)
{
	if (choice == 0 )
	{
		bShouldDrawMenu = false; 
	}

	if (choice == 1 && OnRequest)
		OnRequest(UIRequest::OpenInventoryUI); 

	if (choice == 2 && OnRequest)
		OnRequest(UIRequest::OpenMainMenu);
}
