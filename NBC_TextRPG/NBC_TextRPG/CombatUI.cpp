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

	// 캔버스 그리기 
	DrawCanvasRect();
	// 제목 그리기 
	DrawTitleRect();
	// 스크립트 그리기 
	DrawScriptRect(); 
	// 메뉴 그리기 
	DrawMenuRect();
	
	// 캐릭터 / 적 정보 그리기 
	DrawInfoRects();
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

void CombatUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}


void CombatUI::DrawTitleRect()
{
	DrawRect(titleRect);

	SetCursorPos(titleRect.InnerX() + 42, titleRect.InnerY() + 1);
	cout << "전투";
}

void CombatUI::DrawMenuRect()
{
	menuRect = GetCenteredRect(30, 8);
	menuRect.x += 30;
	menuRect.y += 11;

	DrawRect(menuRect);

	switch (currentState)
	{
	case CombatUIState::Command:
		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
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
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
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
	scriptRect = GetCenteredRect(60, 8);
	scriptRect.x = canvasRect.x;
	scriptRect.y += 11;

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

void CombatUI::DrawInfoRects()
{
	playerInfoRect = GetCenteredRect(30, 4); 
	playerInfoRect.x = canvasRect.InnerX() + 58;
	playerInfoRect.y += 4; 

	MonsterInfoRect = GetCenteredRect(30, 4);
	MonsterInfoRect.x = canvasRect.InnerX() + 1;
	MonsterInfoRect.y = titleRect.InnerY() + 4;

	DrawRect(playerInfoRect);
	DrawRect(MonsterInfoRect);

	SetCursorPos(playerInfoRect.InnerX() + 10, playerInfoRect.InnerY());
	cout << "병권 (150 / 200)";

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());
	cout << "괴물A (100 / 100)";

}

