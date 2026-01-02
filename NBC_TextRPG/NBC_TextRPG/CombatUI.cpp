癤#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"

CombatUI::CombatUI(shared_ptr<Player> player)
{

}

CombatUI::CombatUI()
{
	menus = {
		"몄대",
		"몃깽由",
		"�",
		"媛湲"
	};

	// 예시 
	tempSkills =
	{
		"닿린",
		"紐명 諛移湲",
		"몄由",
		"留移湲"
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
	//ㅽ
	
	switch (currentState)
	{
	case CombatUIState::Command:

		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}

		break;

	case CombatUIState::SkillSelect:
		if (HandleKeyInput(selectedSkillIndex, tempSkills.size()))
		{
			// 몄 濡吏 
			switch (selectedSkillIndex)
			{
			case 0:
				// 닿린  
				PrintLogTest();
				
				break;

			case 1:
				// 紐명듬移湲  
				
				break;

			case 2:
				// 몄 由 
				
				break;

			case 3:
				// 留移湲 
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
	if (choice == 0 ) // 몄대 
	{
		currentState = CombatUIState::SkillSelect;
	}

	if (choice == 1 && OnRequest) // 몃깽由 
	{
		OnRequest(UIRequest::OpenInventoryUI);
	}
	if (choice == 2 && OnRequest) // � 
	{
		OnRequest(UIRequest::OpenStoreUI);
	}
	if (choice == 3 && OnRequest) // 媛湲 
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
				cout << "   " << "[" << menus[i] << "]";
			}

			else
			{
				cout << "    " << menus[i];
			}
		}

		break; 

	case CombatUIState::SkillSelect:

		for (int i = 0; i < tempSkills.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
			if (i == selectedSkillIndex)
			{
				cout << "  ▶ " << "[" << tempSkills[i] << "]";
			}

			else
			{
				cout << "    " << tempSkills[i];
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
		cout << "臾댁 吏?"; 
		break; 

	case CombatUIState::SkillSelect:
		cout << "";
		break; 

	case CombatUIState::Result:
		// 몄 ㅽщ┰... 

		break; 
	}

	

}

void CombatUI::PlayerAttack(Player* player, shared_ptr<Monster> monster)
{
	player->Attack(monster.get());
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "/媛 " << monster->GetMonsterName() << " /瑜 怨듦꺽듬.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << player->stats.attack << " DMG";
}

void CombatUI::MonsterAttack(Player* player, shared_ptr<Monster> monster)
{
	monster->AttackTarget(player);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << monster->GetMonsterName() << "/媛 " << player->stats.name << " /瑜 怨듦꺽듬.";
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
		cout << "�踰 !  �踰: " << player->GetLevel();
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
		//댄 諛
		player->TakeItem(item);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
		cout << "댄 " << item->GetItemInfo().name << " /瑜 듬.";

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
	cout << player->stats.name << "/媛 二쎌듬.";
}

void CombatUI::PrintLogTest()
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "ㅽ ㅽ 異�";
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
	cout << name << "/瑜 留二쇱낀듬.";
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	return make_shared<Monster>(name, player->GetLevel());
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

