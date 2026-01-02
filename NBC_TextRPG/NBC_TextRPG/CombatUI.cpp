#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"

CombatUI::CombatUI()
{
	menus = {
		"싸운다",
		"인벤토리",
		"상점",
		"나가기"
	};
	// 예시 
	skills =
	{
		"할퀴기",
		"몸통 박치기",
		"울음소리",
		"도망치기"
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
	//테스트
	
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
				PrintLogTest();
				
				break;

			case 1:
				// 몸통박치기  
				
				break;

			case 2:
				// 울음 소리 
				
				break;

			case 3:
				// 도망치기 
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

void CombatUI::PlayerAttack(Player* player, shared_ptr<Monster> monster)
{
	player->Attack(monster.get());
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 " << monster->GetMonsterName() << " 을/를 공격했습니다.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << player->stats.attack << " DMG";
}

void CombatUI::MonsterAttack(Player* player, shared_ptr<Monster> monster)
{
	monster->AttackTarget(player);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << monster->GetMonsterName() << "이/가 " << player->stats.name << " 을/를 공격했습니다.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << monster->stats.attack << " DMG";
}

void CombatUI::Battle(Player* player)
{
	shared_ptr<Monster> monster = SpawnMonster(player);
	PlayerAttack(player, monster);
	MonsterAttack(player, monster);
	
}


void CombatUI::GetExp(Player* player)
{
	int inExp = 50;
	player->TakeExp(inExp);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "+" << inExp << " EXP";
	if (player->GetExp() >= 100)
	{
		player->SetExp(0);
		player->LevelUp();
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
	}
	
}

void CombatUI::GetGold(Player* player)
{
	int inGold = Random::Choice(10, 20);
	player->TakeGold(inGold);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << "+" << inGold << " Gold";
}

void CombatUI::DropItem(Player* player)
{
	double percent = 0.3;
	if (Random::Success(percent))
	{
		Item* item = nullptr;
		//아이템 반환
		player->TakeItem(item);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
		cout << "아이템 " << item->GetItemInfo().name << " 을/를 획득했습니다.";

	}
}

void CombatUI::VictoryEvnet(Player* player)
{
	GetExp(player);
	GetGold(player);
	DropItem(player);
}
	

void CombatUI::DefeatEvnet(Player* player)
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 죽었습니다.";
}

void CombatUI::PrintLogTest()
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "테스트 텍스트 출력";
}

shared_ptr<Monster> CombatUI::SpawnMonster(Player* player)
{
	string name;
	switch (Random::Choice(1, 3))
	{
	case 1:
		name = "Weak Monster";
		break;

	case 2:
		name = "Normal Monster";
		break;

	case 3:
		name = "Strong Monster";
		break;

	}

	if (player->GetLevel() >= 10)
	{
		name = "Boss Monster";
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << name << "을/를 마주쳤습니다.";
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	return make_shared<Monster>(name, player->GetLevel());
}

